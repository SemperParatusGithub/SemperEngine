#include "TestLayer.h"

#include <GLFW/include/GLFW/glfw3.h>


TestLayer::TestLayer() : Layer("Test Layer"),
	m_CameraController(1280.0f / 720.0f, 0.0f, 0.0f),
	m_GridTexture(nullptr),
	m_StoneTexture(nullptr),
	m_BrickTexture(nullptr)
{
}

void TestLayer::OnAttach()
{
	m_GridTexture = SemperEngine::Texture2D::Create("Grid.png");
	m_StoneTexture = SemperEngine::Texture2D::Create("StoneTex.jpg");
	m_BrickTexture = SemperEngine::Texture2D::Create("BrickTex.png");

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

	for(int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
		{
			transform.SetTranslation(SemperEngine::Vec3((float) y, (float) x, 0.0f));
			SemperEngine::Batcher2D::DrawQuad(transform, SemperEngine::Vec4((float) x / 10.0f, (float) y / 10.0f, 0.0f, 1.0f));
		}

	SemperEngine::Transform textureTransform;
	textureTransform.SetScale(SemperEngine::Vec3(2.0f, 2.0f, 1.0f));

	textureTransform.SetTranslation(SemperEngine::Vec3(-2.0f, 0.0f, 0.0f));
	SemperEngine::Batcher2D::DrawQuad(textureTransform, m_StoneTexture);

	textureTransform.SetTranslation(SemperEngine::Vec3(-2.0f, 3.0f, 0.0f));
	SemperEngine::Batcher2D::DrawQuad(textureTransform, m_BrickTexture);

	SemperEngine::Batcher2D::EndScene();
}

void TestLayer::OnImGuiRender()
{
	ImGui::Begin("Test Layer");
	ImGui::Text("Framerate: %.2f FPS", ImGui::GetIO().Framerate);
	ImGui::End();
}

void TestLayer::OnEvent(SemperEngine::Event &e)
{
	m_CameraController.OnEvent(e);
}