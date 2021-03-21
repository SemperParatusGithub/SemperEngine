#include "EditorLayer.h"

#include <GLFW/include/GLFW/glfw3.h>

#include "SemperEngine/Graphics/Renderers/SceneRenderer.h"

#include "ImGuizmo/ImGuizmo.h"
#include "SemperEngine/Util/Math.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "SemperEngine/Util/Filesystem.h"


EditorLayer::EditorLayer() :
	Layer("Editor Layer"),
	m_ViewportSize({ 1280, 720 }),
	m_SceneViewPortFocused(false), m_SceneViewPortHovered(false),
	m_ViewportSizeChanged(false)
{
	Log::EnableEditorLogConsole();
	Log::EnableAutoFlush();

	m_Scene = MakeUnique<Scene>();
	m_Hierarchy = MakeShared<Hierarchy>(m_Scene);
	m_Inspector = MakeShared<Inspector>(m_Scene);

	m_PlayButtonTexture = Texture2D::Create("Assets/Textures/PlayButton.png");
	m_PauseButtonTexture = Texture2D::Create("Assets/Textures/PauseButton.png");
	m_ExitButtonTexture = Texture2D::Create("Assets/Textures/ExitButton.png");
}

void EditorLayer::OnAttach()
{
	EngineApplication::Instance().GetWindow().SetInterval(0);
	EngineApplication::Instance().GetWindow().Maximize();
}

void EditorLayer::OnDetach()
{
}

void EditorLayer::OnUpdate(float deltaTime)
{
	if (m_SceneViewPortHovered && !m_Scene->IsPlaying())
		m_EditorCamera.OnUpdate(deltaTime);

	UpdateWindowTitle();

	bool allowEvents = m_SceneViewPortHovered || m_SceneViewPortFocused;
	EngineApplication::Instance().BlockImGuiEvents(!allowEvents);

	if (m_ViewportSizeChanged)
	{
		m_EditorCamera.OnResize(static_cast<U32>(m_ViewportSize.x), static_cast<U32>(m_ViewportSize.y));
		m_Scene->OnResize(static_cast<U32>(m_ViewportSize.x), static_cast<U32>(m_ViewportSize.y));
		m_ViewportSizeChanged = false;
	}

	// Gizmos
	if (Input::IsKeyPressed(Key::LeftControl) && !ImGuizmo::IsUsing())
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

	// Update
	m_Scene->OnUpdate(deltaTime, m_EditorCamera);
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
			if (ImGui::MenuItem("Open...", "Ctrl+O"))
				OpenScene();
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
				SaveSceneAs();
			if (ImGui::MenuItem("Exit"))
				EngineApplication::Instance().Close();
				
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::ShowDemoWindow();

	m_Hierarchy->OnImGui();
	m_Inspector->OnImGui(m_Hierarchy->GetSelectedEntity());
	m_EditorCamera.OnImGui();

	Renderer::OnImGui();
	SceneRenderer::OnImGui();
	Log::OnEditorLogConsoleGui();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 { 0, 0 });
	ImGui::Begin("Scene Viewport");

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.8f, 0.8f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));

	ImGui::SetCursorPosX(ImGui::GetContentRegionAvailWidth() * 0.5f - 48.0f);

	if (ImGui::ImageButton(m_PlayButtonTexture->GetHandle(), { 32.0f, 32.0f }))
	{
		m_Scene->Play();
		m_ImGuizmoOperation = -1;
		SE_CORE_INFO("Playing Scene");
	}

	ImGui::SameLine();

	if (ImGui::ImageButton(m_PauseButtonTexture->GetHandle(), { 32.0f, 32.0f }))
	{
		m_Scene->Pause();
		SE_CORE_INFO("Pausing Scene");
	}

	ImGui::SameLine();

	if (ImGui::ImageButton(m_ExitButtonTexture->GetHandle(), { 32.0f, 32.0f }))
	{
		m_Scene->ReturnToEditing();
		SE_CORE_INFO("Return");
	}

	ImGui::PopStyleColor(3);
	ImGui::PopStyleVar(3);

	m_ViewportPosition = {
		ImGui::GetWindowPos().x + ImGui::GetCursorPos().x,
		ImGui::GetWindowPos().y + ImGui::GetCursorPos().y 
	};
	Vec2f newViewportSize = {
		ImGui::GetWindowSize().x - ImGui::GetCursorPos().x,
		ImGui::GetWindowSize().y - ImGui::GetCursorPos().y
	};
	if (newViewportSize != m_ViewportSize) {
		m_ViewportSize = newViewportSize;
		m_ViewportSizeChanged = true;
	}

	m_SceneViewPortFocused = ImGui::IsWindowFocused();
	m_SceneViewPortHovered = ImGui::IsWindowHovered();

	ImGui::Image(SceneRenderer::GetFinalFramebufferColorAttachmentHandle(), { m_ViewportSize.x, m_ViewportSize.y }, ImVec2 { 0, 1 }, ImVec2 { 1, 0 });

	// Gizmos
	Entity activeEntity = m_Hierarchy->GetSelectedEntity();
	if (activeEntity && m_ImGuizmoOperation != -1)
	{
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();
		ImGuizmo::SetRect(m_ViewportPosition.x, m_ViewportPosition.y, m_ViewportSize.x, m_ViewportSize.y);
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

void EditorLayer::OpenScene()
{
	std::string filepath = Filesystem::OpenFileDialog("Semper Scene (*.semper)\0*.semper\0");
	if (!filepath.empty())
	{
		m_Scene->Deserialize(filepath);
	}
}

void EditorLayer::SaveSceneAs()
{
	std::string filepath = Filesystem::SaveFileDialog("Semper Scene (*.semper)\0*.semper\0");
	if (!filepath.empty())
	{
		m_Scene->Serialize(filepath);
	}
}

void EditorLayer::UpdateWindowTitle()
{
	std::string title = "Semper Editor - ";

	title += m_Scene->GetName() + " " + m_Scene->GetVersion();
	title += " - ";

#if defined(SE_DEBUG)
	title += "Debug-x64";
#elif defined(SE_RELEASED)
	title += "Release-x64";
#endif

	EngineApplication::Instance().GetWindow().SetTitle(title);
}