#include "TestLayer.h"

#if 0

#include <GLFW/include/GLFW/glfw3.h>


TestLayer::TestLayer() : Layer("Test Layer"),
	m_CameraController(1280.0f / 720.0f, 0.0f, 0.0f)
{
}

void TestLayer::OnAttach()
{
	m_GridTexture.reset(Texture2D::Create("Grid.png"));
	m_StoneTexture.reset(Texture2D::Create("StoneTex.jpg"));
	m_BrickTexture.reset(Texture2D::Create("BrickTex.png"));

	TextureData data;
	data.magFilter = TextureFilter::Nearest;
	data.minFilter = TextureFilter::Nearest;
	m_SpriteSheet.reset(Texture2D::Create("roadTextures_tilesheet.png", data));

	Renderer::SetClearColor(Vec4(0.7f, 0.7f, 0.7f, 0.7f));
}

void TestLayer::OnDetach()
{
}

void TestLayer::OnUpdate(float deltaTime)
{
	m_CameraController.OnUpdate(deltaTime);

	Renderer::Clear();
	Batcher2D::BeginScene(m_CameraController.GetCamera());

	for(auto &[name, sprite] : m_Sprites)
		Batcher2D::Draw(&sprite);

	Batcher2D::EndScene();
}

void TestLayer::OnImGuiRender()
{
	
	ImGui::Begin("SpriteSheet");
	ImTextureID textureID = (ImTextureID) m_SpriteSheet->GetHandle();
	float width = ImGui::GetContentRegionAvailWidth();
	ImVec2 size = { width, width * m_SpriteSheet->GetHeight() / m_SpriteSheet->GetWidth() };
	ImGui::Image(textureID, size, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
	ImGui::End();

	ImGui::Begin("Test Layer");

	static int index[2] = { 0, 0 };
	ImGui::DragInt2("Index", index);

	if (ImGui::Button("Create Sprite"))
	{
		static U32 ID = 0;
		ID++;

		std::string name = std::string("Sprite" + std::to_string(ID));
		Sprite sprite = Sprite(m_SpriteSheet, Vec2(index[0], index[1]), Vec2(64.0f, 64.0f), Vec2(1.0f, 1.0f));
		sprite.SetPosition(Vec2(0.0f, 0.0f));

		m_Sprites.push_back(std::make_pair(name, sprite));
	}
	ImGui::End();

	if (!m_Sprites.empty())
	{
		ImGui::Begin("Sprites");
		for (auto &[name, sprite] : m_Sprites)
		{
			if (ImGui::CollapsingHeader(name.c_str()))
			{
				ImGui::PushID(name.c_str());

				float position[2] = { sprite.GetPosition().x, sprite.GetPosition().y };
				ImGui::DragFloat2("Position", position, 0.1f, -10.0f, 10.0f);
				sprite.SetPosition(Vec2(position[0], position[1]));

				ImGui::PopID();
			}
		}
		ImGui::End();
	}
}

void TestLayer::OnEvent(Event &e)
{
	m_CameraController.OnEvent(e);
}
#endif