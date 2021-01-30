#include "EditorLayer.h"
#include "SemperEngine/Core/EngineApplication.h"

#include <GLFW/include/GLFW/glfw3.h>


EditorLayer::EditorLayer() :
	Layer("Editor Layer"),
	m_ViewportSize({ 1280, 720 }),
	m_SceneViewPortFocused(false), m_SceneViewPortHovered(false)
{
	FramebufferInfo info = { 1280, 720 };
	m_Framebuffer.reset(Framebuffer::Create(info));

	m_LogConsole = MakeShared<LogConsole>();
	Log::SetLogConsoleInstance(m_LogConsole);

	m_Scene = MakeUnique<Scene>();
	m_Hierarchy = MakeShared<Hierarchy>(m_Scene);
	m_Inspector = MakeShared<Inspector>(m_Scene);

	m_EditorCamera.Set2D();
}

void EditorLayer::OnAttach()
{
	EngineApplication::Instance().GetWindow().SetInterval(0);
}

void EditorLayer::OnDetach()
{
}

void EditorLayer::OnUpdate(float deltaTime)
{
	if (m_SceneViewPortHovered && Input::IsKeyPressed(Key::LeftShift))
		m_EditorCamera.OnUpdate(deltaTime);

	bool allowEvents = m_SceneViewPortHovered;
	EngineApplication::Instance().BlockImGuiEvents(!allowEvents);

	if (m_Framebuffer->GetSize() != m_ViewportSize) 
	{
		m_Framebuffer->OnResize((U32) m_ViewportSize.x, (U32) m_ViewportSize.y);
		m_EditorCamera.SetBounds((float) m_ViewportSize.x, (float) m_ViewportSize.y);
	}

	// Render
	{
		m_Framebuffer->Bind();

		Renderer::SetClearColor({ 0.86f,  0.86f,  0.86f,  0.86f });
		Renderer::Clear();

		m_Scene->OnUpdateEditor(deltaTime, m_EditorCamera);

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
				EngineApplication::Instance().Close();
				
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Begin("Metrics");

	if (ImGui::CollapsingHeader("General"))
	{
		ImGui::Text("Framerate: %.2f FPS", EngineApplication::Instance().GetFramerate());
		ImGui::Text("Frametime: %.2f ms", EngineApplication::Instance().GetFrametime());
		ImGui::Separator();
		ImGui::Text("Render API: %s", Renderer::GetRenderAPIString().c_str());
		ImGui::Text("Vendor: %s", Renderer::GetVendor().c_str());
		ImGui::Text("Renderer: %s", Renderer::GetRenderer().c_str());
		ImGui::Text("Version: %s", Renderer::GetVersion().c_str());
	}

	auto metrics = Batcher2D::GetMetrics();
	if (ImGui::CollapsingHeader("Batcher2D Metrics"))
	{
		ImGui::Text("Batches: %d", metrics.batches);
		ImGui::Text("Vertices: %d", metrics.vertices);
		ImGui::Text("Indices: %d", metrics.indices);
		ImGui::Text("Triangles: %d", metrics.triangles);
	}
	Batcher2D::ResetMetrics(); 

	auto &io = ImGui::GetIO();
	if (ImGui::CollapsingHeader("ImGui Metrics"))
	{
		ImGui::Text("Vertices: %d", io.MetricsRenderVertices);
		ImGui::Text("Indices: %d", io.MetricsRenderIndices);
		ImGui::Text("%d active windows (%d visible)", io.MetricsActiveWindows, io.MetricsRenderWindows);
		ImGui::Text("Triangles: %d", metrics.triangles);
	}
	ImGui::End();

	ImGui::ShowDemoWindow();

	ImGui::Begin("Test Window 3");
	ImGui::Text("Hello World!");
	ImGui::End();

	m_Hierarchy->OnImGui();
	m_Inspector->OnImGui(m_Hierarchy->GetSelectedEntity());

	m_EditorCamera.OnImGui();

	m_LogConsole->OnImGuiRender();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 { 0, 0 });
	ImGui::Begin("Scene Viewport");

	m_SceneViewPortFocused = ImGui::IsWindowFocused();
	m_SceneViewPortHovered = ImGui::IsWindowHovered();

	ImVec2 size = ImGui::GetContentRegionAvail();
	m_ViewportSize = { (int) size.x, (int) size.y };

	uint64_t textureID = reinterpret_cast<U64>(m_Framebuffer->GetColorAttachmentHandle());
	ImGui::Image(reinterpret_cast<ImTextureID>(textureID), size, ImVec2 { 0, 1 }, ImVec2 { 1, 0 });

	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::End(); // Dock space
}

void EditorLayer::OnEvent(Event &e)
{
	m_EditorCamera.OnEvent(e);
}