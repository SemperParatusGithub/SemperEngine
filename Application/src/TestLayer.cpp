#include "TestLayer.h"

#include <GLFW/include/GLFW/glfw3.h>


TestLayer::TestLayer() : Layer("Test Layer"),
	m_CameraController(1280.0f / 720.0f, 0.0f, 0.0f),
	m_GridTexture(nullptr),
	m_StoneTexture(nullptr),
	m_BrickTexture(nullptr),
	m_SpriteSheet(nullptr)
{
}

void TestLayer::OnAttach()
{
	m_GridTexture = SemperEngine::Texture2D::Create("Grid.png");
	m_StoneTexture = SemperEngine::Texture2D::Create("StoneTex.jpg");
	m_BrickTexture = SemperEngine::Texture2D::Create("BrickTex.png");

	SemperEngine::TextureData data;
	data.magFilter = SemperEngine::TextureFilter::Nearest;
	data.minFilter = SemperEngine::TextureFilter::Nearest;
	m_SpriteSheet = SemperEngine::Texture2D::Create("roadTextures_tilesheet.png", data);

	SemperEngine::Renderer::SetClearColor(SemperEngine::Vec4(0.7f, 0.7f, 0.7f, 0.7f));
}

void TestLayer::OnDetach()
{
}

void TestLayer::OnUpdate(float deltaTime)
{
	m_CameraController.OnUpdate(deltaTime);

	SemperEngine::Renderer::Clear();
	SemperEngine::Batcher2D::BeginScene(m_CameraController.GetCamera());

	SemperEngine::Transform transform;
	transform.SetRotation(SemperEngine::Vec3(0.0f, 0.0f, (float) glfwGetTime()));

	for(float y = 0; y < 10.0f; y += 1.0f)
		for (float x = 0; x < 10.0f; x += 1.0f)
		{
			transform.SetTranslation({ x + 3.0f, y, 0.0f });
			SemperEngine::Batcher2D::DrawQuad(transform, { x / 10.0f, y / 10.0f, 0.0f, 1.0f });
		}

	SemperEngine::Transform gridTransform({ -10.0f, 5.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 10.0f, 10.0f, 1.0f });
	SemperEngine::Batcher2D::DrawQuad(gridTransform, m_GridTexture);

	SemperEngine::Transform brickTransform({ 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
	SemperEngine::Batcher2D::DrawQuad(brickTransform, m_BrickTexture);

	for(auto &s : m_Sprites)
		SemperEngine::Batcher2D::Draw(&s.sprite);

	SemperEngine::Batcher2D::EndScene();
}

void TestLayer::OnImGuiRender()
{
	ImGui::Begin("Test Layer");
	ImGui::Text("Framerate: %.2f FPS", ImGui::GetIO().Framerate);

	ImGui::Separator();

	static int index[2] = { 0, 0 };
	static float pos[2] = { 0.0f, 0.0f };
	ImGui::InputFloat2("Position##Initial", pos);
	ImGui::InputInt2("Index##Initial", index);

	if (ImGui::Button("Create Sprite"))
	{
		static SemperEngine::U32 id = 0;
		id++;

		std::string name = std::string("Sprite" + std::to_string(id));
		SemperEngine::Sprite sprite = { m_SpriteSheet, { index[0], index[1] }, { 64.0f, 64.0f }, { 1.0f, 2.0f } };
		sprite.SetPosition({ pos[0], pos[1] });

		m_Sprites.push_back({ name, sprite, pos[0], pos[1], index[0], index[1] });
		
	}
	ImGui::End();

	if (!m_Sprites.empty())
	{
		ImGui::Begin("Sprites");
		for (auto &s : m_Sprites)
		{
			if (ImGui::CollapsingHeader(s.name.c_str()))
			{
				std::string nameX = "Position (x): ##" + s.name;
				std::string nameY = "Position (y): ##" + s.name;

				ImGui::DragFloat(nameX.c_str(), &s.posX, 0.1f, -10.0f, 10.0f);
				ImGui::DragFloat(nameY.c_str(), &s.posY, 0.1f, -10.0f, 10.0f);

				s.sprite.SetPosition({ s.posX, s.posY });
				s.sprite.SetSpriteSheet(m_SpriteSheet, { s.indexX, s.indexY }, { 64.0f, 64.0f }, { 1.0f, 1.0f });
			}
		}
		ImGui::End();
	}
}

void TestLayer::OnEvent(SemperEngine::Event &e)
{
	m_CameraController.OnEvent(e);
}