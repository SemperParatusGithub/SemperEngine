#include "EditorLayer.h"
#include "SemperEngine/Core/EngineApplication.h"



EditorLayer::EditorLayer() :
	m_CameraController(1280.0f / 720.0f, 0.0f, 0.0f),
	m_SceneViewPortFocused(false),	m_SceneViewPortHovered(false)
{
	SemperEngine::FramebufferInfo info = { 1280, 720 };
	m_Framebuffer = SemperEngine::Framebuffer::Create(info);

	m_TestTexture = SemperEngine::Texture2D::Create("roadTextures_tilesheet.png");
}

void EditorLayer::OnAttach()
{
	ImGui::GetIO().FontDefault = ImGui::GetIO().Fonts->AddFontFromFileTTF("bahnschrift.ttf", 24);
}

void EditorLayer::OnDetach()
{
}

void EditorLayer::OnUpdate(float deltaTime)
{
	if(m_SceneViewPortFocused && m_SceneViewPortHovered)
		m_CameraController.OnUpdate(deltaTime);

	bool allowEvents = m_SceneViewPortHovered;
	SemperEngine::EngineApplication::Instance().BlockImGuiEvents(!allowEvents);

	SemperEngine::Transform quadTransform;
	float ratio = (float) m_TestTexture->GetWidth() / (float) m_TestTexture->GetHeight();
	quadTransform.SetScale({ ratio, 1.0f, 1.0f }); 

	m_Framebuffer->Bind();

	SemperEngine::Renderer::SetClearColor({ 0.7f,  0.7f,  0.7f,  0.7f });
	SemperEngine::Renderer::Clear();

	SemperEngine::Batcher2D::BeginScene(m_CameraController.GetCamera());
	SemperEngine::Batcher2D::DrawQuad(quadTransform, m_TestTexture);
	SemperEngine::Batcher2D::EndScene();

	m_Framebuffer->UnBind();
}

void EditorLayer::OnImGuiRender()
{
	ImGuiWindowFlags dockSpaceWindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGuiViewport *viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", 0, dockSpaceWindowFlags);
	ImGui::PopStyleVar(3);

	ImGuiID dockSpaceID = ImGui::GetID("DockSpace");
	ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New", "Ctrl+N"));
			if (ImGui::MenuItem("Open...", "Ctrl+O"));
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"));
			if (ImGui::MenuItem("Exit"));
				
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Begin("Test Window 1");
	ImGui::End();

	ImGui::Begin("Test Window 2");
	ImGui::End();

	ImGui::Begin("Test Window 3");
	ImGui::End();

	ImGui::Begin("Scene Viewport");
	m_SceneViewPortFocused = ImGui::IsWindowFocused();
	m_SceneViewPortHovered = ImGui::IsWindowHovered();
	uint64_t textureID = reinterpret_cast<uint32_t>(m_Framebuffer->GetColorAttachmentHandle());
	ImGui::Image(reinterpret_cast<ImTextureID>(textureID), ImGui::GetContentRegionAvail(), ImVec2 { 0, 1 }, ImVec2 { 1, 0 });
	ImGui::End();

	ImGui::End(); // Dockspace
}

void EditorLayer::OnEvent(SemperEngine::Event &e)
{
	m_CameraController.OnEvent(e);
}