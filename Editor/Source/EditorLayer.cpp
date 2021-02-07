#include "EditorLayer.h"
#include "SemperEngine/Core/EngineApplication.h"

#include <GLFW/include/GLFW/glfw3.h>

#include "ImGuizmo/ImGuizmo.h"
#include "SemperEngine/Util/Math.h"


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

	m_EditorCamera.Set3D();
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

	bool allowEvents = m_SceneViewPortHovered || m_SceneViewPortFocused;
	EngineApplication::Instance().BlockImGuiEvents(!allowEvents);

	if (m_Framebuffer->GetSize() != m_ViewportSize) 
	{
		m_Framebuffer->OnResize((U32) m_ViewportSize.x, (U32) m_ViewportSize.y);
		m_EditorCamera.SetBounds((float) m_ViewportSize.x, (float) m_ViewportSize.y);
	}

	// Gizmos
	if (Input::IsKeyPressed(Key::LeftControl))
	{
		if (Input::IsKeyPressed(Key::D1))
			m_ImGuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
		if(Input::IsKeyPressed(Key::D2))
			m_ImGuizmoOperation = ImGuizmo::OPERATION::ROTATE;
		if(Input::IsKeyPressed(Key::D3))
			m_ImGuizmoOperation = ImGuizmo::OPERATION::SCALE;
		if(Input::IsKeyPressed(Key::D0))
			m_ImGuizmoOperation = -1;
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
	if (ImGui::Button("Serialize"))
		m_Scene->Serialize("TestScene.xml");
	if (ImGui::Button("Deserialize"))
		m_Scene->Deserialize("TestScene.xml");
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

	// Gizmos
	Entity activeEntity = m_Hierarchy->GetSelectedEntity();
	if (activeEntity && m_ImGuizmoOperation != -1)
	{
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, size.x, size.y);
		ConstRef<Mat4> view = m_EditorCamera.GetView();
		ConstRef<Mat4> proj = m_EditorCamera.GetProjection();

		auto &tc = activeEntity.Get<TransformComponent>();
		Mat4 transform = tc.transform.GetTransform();

		bool snap = Input::IsKeyPressed(Key::LeftControl);
		float snapValue = m_ImGuizmoOperation == ImGuizmo::OPERATION::ROTATE ? 45.0f : 0.5f;

		float snapValues[3] = { snapValue, snapValue, snapValue };

		ImGuizmo::Manipulate(&view[0][0], &proj[0][0], (ImGuizmo::OPERATION) m_ImGuizmoOperation,
			ImGuizmo::LOCAL, &transform[0][0], nullptr, snap ? snapValues : nullptr);

		if (ImGuizmo::IsUsing())
		{
			auto [translation, rotation, scale] = Util::Decompose(transform);

			glm::vec3 deltaRotation = rotation - tc.transform.GetRotation();

			if(m_ImGuizmoOperation == ImGuizmo::OPERATION::TRANSLATE)
				tc.SetTranslation(translation);
			if (m_ImGuizmoOperation == ImGuizmo::OPERATION::ROTATE)
				tc.transform.Rotate(deltaRotation);
			if (m_ImGuizmoOperation == ImGuizmo::OPERATION::SCALE)
				tc.SetScale(scale);
		}
	}

	ImGui::End();	// Viewport
	ImGui::PopStyleVar();

	ImGui::End(); // Dock space
}

void EditorLayer::OnEvent(Event &e)
{
	m_EditorCamera.OnEvent(e);
}