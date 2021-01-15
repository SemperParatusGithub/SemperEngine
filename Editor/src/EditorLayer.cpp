#include "EditorLayer.h"
#include "SemperEngine/Core/EngineApplication.h"

#include <GLFW/include/GLFW/glfw3.h>

struct TestComponent
{
	float x, y;
};


EditorLayer::EditorLayer() :
	Layer("Editor Layer"),
	m_CameraController(1280.0f / 720.0f, 0.0f, 0.0f),
	m_SceneViewPortFocused(false), m_SceneViewPortHovered(false)
{
	m_LogConsole = SemperEngine::MakeShared<SemperEngine::LogConsole>();
	SemperEngine::Log::SetLogConsoleInstance(m_LogConsole);

	m_CameraController.SetZoom(7.5f);

	SE_CORE_INFO("Hello World");
	SE_CORE_WARN("This is a Warning");
	SE_CORE_ERROR("Error!");

	m_Scene = SemperEngine::MakeUnique<SemperEngine::Scene>();

	m_TestEntity = m_Scene->CreateEntity();
	m_TestEntity.Add<TestComponent>(TestComponent { 12.0f, 27.0f });

	SE_CLIENT_INFO("Test Entity has TestComponent: %d", m_TestEntity.Has<TestComponent>());

	auto pos = m_TestEntity.Get<TestComponent>();
	SE_CLIENT_INFO("Test Entity data: %.2f, %.2f", pos.x, pos.y);

	SemperEngine::FramebufferInfo info = { 1280, 720 };
	m_Framebuffer = SemperEngine::Framebuffer::Create(info);

	m_TestTexture = SemperEngine::Texture2D::Create("Checkerboard.png");
}

void EditorLayer::OnAttach()
{
	ImGui::GetIO().FontDefault = ImGui::GetIO().Fonts->AddFontFromFileTTF("OpenSans-Regular.ttf", 22); // ImGui::GetIO().Fonts->AddFontFromFileTTF("bahnschrift.ttf", 21);
	ImGui::GetIO().Fonts->AddFontFromFileTTF("OpenSans-Regular.ttf", 20);

	SemperEngine::EngineApplication::Instance().GetWindow().SetInterval(0);
}

void EditorLayer::OnDetach()
{
}

void EditorLayer::OnUpdate(float deltaTime)
{
	if (m_SceneViewPortFocused && m_SceneViewPortHovered)
		m_CameraController.OnUpdate(deltaTime);

	bool allowEvents = m_SceneViewPortHovered;
	SemperEngine::EngineApplication::Instance().BlockImGuiEvents(!allowEvents);

	SemperEngine::Transform quadTransform;
	float ratio = (float) m_TestTexture->GetWidth() / (float) m_TestTexture->GetHeight();
	quadTransform.SetScale({ ratio, 1.0f, 1.0f });

	{
		m_Framebuffer->Bind();

		SemperEngine::Renderer::SetClearColor({ 0.86f,  0.86f,  0.86f,  0.86f });
		SemperEngine::Renderer::Clear();

		SemperEngine::Batcher2D::BeginScene(m_CameraController.GetCamera());

		SemperEngine::Transform transform;
		transform.SetRotation(SemperEngine::Vec3(0.0f, 0.0f, (float) glfwGetTime()));

		for (float y = 0; y < 25.0f; y += 1.0f)
			for (float x = 0; x < 25.0f; x += 1.0f)
			{
				transform.SetTranslation({ x -12.0f, y -12.0f, 0.0f });
				SemperEngine::Batcher2D::DrawQuad(transform, { x / 25.0f, y / 25.0f, 0.0f, 1.0f });
			}

		SemperEngine::Transform checkerBoardTransform;
		checkerBoardTransform.SetScale({ 30.0f, 30.0f, 1.0f });
		SemperEngine::Batcher2D::DrawQuad(checkerBoardTransform, m_TestTexture);

		SemperEngine::Batcher2D::EndScene();

		m_Framebuffer->UnBind();
	}
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
			if (ImGui::MenuItem("Exit"))
				SemperEngine::EngineApplication::Instance().Close();
				
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	auto metrics = SemperEngine::Batcher2D::GetMetrics();
	ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);	// OpenSans-Regular
	ImGui::Begin("Batcher 2D Metrics");
	ImGui::Text("Batches: %d", metrics.batches);
	ImGui::Text("Vertices: %d", metrics.vertices);
	ImGui::Text("Indices: %d", metrics.indices);
	ImGui::Text("Triangles: %d", metrics.triangles);
	ImGui::End();
	ImGui::PopFont();									// OpenSans-Regular
	SemperEngine::Batcher2D::ResetMetrics();

	ImGui::Begin("Test Window 2");
	ImGui::End();

	ImGui::ShowDemoWindow();

	ImGui::Begin("Test Window 3");
	ImGui::Text("Framerate: %d FPS", (int) ImGui::GetIO().Framerate);
	ImGui::End();

	m_LogConsole->OnImGuiRender();

	char buf[128];
	sprintf_s(buf, 128, "Scene Viewport (%d) ###AnimatedTitle", (int)ImGui::GetIO().Framerate);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 { 0, 0 });
	ImGui::Begin(buf);

	m_SceneViewPortFocused = ImGui::IsWindowFocused();
	m_SceneViewPortHovered = ImGui::IsWindowHovered();

	glm::vec2 currentViewportSize = { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y };
	if (currentViewportSize != m_ViewportSize) {
		m_ViewportSize = currentViewportSize;
		m_Framebuffer->OnResize((SemperEngine::U32)m_ViewportSize.x, (SemperEngine::U32)m_ViewportSize.y);
		m_CameraController.SetBounds(m_ViewportSize.x, m_ViewportSize.y);
		SE_CLIENT_INFO("Viewport resized: %.2f, %.2f", m_ViewportSize.x, m_ViewportSize.y);
	}

	uint64_t textureID = reinterpret_cast<uint32_t>(m_Framebuffer->GetColorAttachmentHandle());
	ImGui::Image(reinterpret_cast<ImTextureID>(textureID), ImGui::GetContentRegionAvail(), ImVec2 { 0, 1 }, ImVec2 { 1, 0 });
	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::End(); // Dockspace
}

void EditorLayer::OnEvent(SemperEngine::Event &e)
{
	m_CameraController.OnEvent(e);
}