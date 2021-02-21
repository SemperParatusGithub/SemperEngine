#include "EditorLayer.h"

#include <GLFW/include/GLFW/glfw3.h>

#include "ImGuizmo/ImGuizmo.h"
#include "SemperEngine/Util/Math.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "SemperEngine/Util/Filesystem.h"


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

	m_PlayButtonTexture = Texture2D::Create("Assets/Textures/PlayButton.png");
	m_PauseButtonTexture = Texture2D::Create("Assets/Textures/PauseButton.png");
	m_ExitButtonTexture = Texture2D::Create("Assets/Textures/ExitButton.png");

	class CameraController : public ScriptableEntity
	{
	public:
		virtual void OnCreate() override
		{
			constexpr float rotationX = glm::radians(-20.0f);
			Get<TransformComponent>().SetRotation(Vec3(rotationX, 0.0f, 0.0f));
		}
		virtual void OnUpdate(float dt) override
		{
			auto &transform = Get<TransformComponent>();

			transform.Rotate(Vec3(0.0f, m_RotationSpeed * dt, 0.0f));

			Vec3 position = m_FocalPoint - GetForwardDirection() * m_Zoom;
			transform.SetTranslation(position);
		}	
		virtual void OnGui() override
		{
			ImGui::SliderFloat("Zoom", &m_Zoom, 0.1f, 10.0f);
			ImGui::SliderFloat("Rotation Speed", &m_RotationSpeed, 0.0f, 50.0f);
		}
		virtual void OnDestroy() override
		{
		}

		Vec3 GetForwardDirection() 
		{
			Vec3 rotation = Get<TransformComponent>().transform.GetRotation();
			return glm::rotate(glm::quat(rotation), Vec3(0.0f, 0.0f, -1.0f));
		}

	private:
		Vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };
		float m_Zoom = 10.0f;
		float m_RotationSpeed = 1.0f;
	};

	// Example Scene
	{
		m_CameraEntity = m_Scene->CreateEntity("Main Scene Camera");

		auto &cam = m_CameraEntity.Add<SceneCameraComponent>();
		cam.primary = true;

		auto &nsc = m_CameraEntity.Add<NativeScriptComponent>();
		nsc.AttachScript<CameraController>();

		m_DirtEntity = m_Scene->CreateEntity("ground");

		auto &sc = m_DirtEntity.Add<SpriteComponent>();
		SharedPtr<Texture2D> groundTex = Texture2D::Create("Assets/Textures/StoneTex.jpg");
		sc.SetTexture(groundTex);

		auto &tc = m_DirtEntity.Get<TransformComponent>();
		tc.SetRotation(Vec3(glm::radians(90.0f), 0.0f, 0.0f));
		tc.SetScale(Vec3(5.0f, 5.0f, 1.0f));

		m_SquareEntity = m_Scene->CreateEntity("Square");

		m_SquareEntity.Add<SpriteComponent>();
		m_SquareEntity.Get<TransformComponent>().SetTranslation(Vec3(0.0f, 0.5f, 0.0f));
	}
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
	if (m_SceneViewPortHovered && !m_Scene->IsPlaying())
		m_EditorCamera.OnUpdate(deltaTime);

	bool allowEvents = m_SceneViewPortHovered || m_SceneViewPortFocused;
	EngineApplication::Instance().BlockImGuiEvents(!allowEvents);

	if (m_Framebuffer->GetSize() != static_cast<Vec2i>(m_ViewportSize)) 
	{
		m_Framebuffer->OnResize(static_cast<U32>(m_ViewportSize.x), static_cast<U32>(m_ViewportSize.y));
		m_EditorCamera.SetBounds(m_ViewportSize.x, m_ViewportSize.y);
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

	// Render
	{
		m_Framebuffer->Bind();

		Renderer::SetClearColor({ 0.86f,  0.86f,  0.86f,  0.86f });
		Renderer::Clear();

		m_Scene->OnUpdate(deltaTime, m_EditorCamera, m_ViewportSize);

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

	m_LogConsole->OnImGuiRender();

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
	m_ViewportSize = {
		ImGui::GetWindowSize().x - ImGui::GetCursorPos().x,
		ImGui::GetWindowSize().y - ImGui::GetCursorPos().y
	};

	m_SceneViewPortFocused = ImGui::IsWindowFocused();
	m_SceneViewPortHovered = ImGui::IsWindowHovered();

	uint64_t textureID = reinterpret_cast<U64>(m_Framebuffer->GetColorAttachmentHandle());

	ImGui::Image(reinterpret_cast<ImTextureID>(textureID), { m_ViewportSize.x, m_ViewportSize.y }, ImVec2 { 0, 1 }, ImVec2 { 1, 0 });

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