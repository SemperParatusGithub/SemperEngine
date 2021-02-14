#include "Precompiled.h"
#include "EditorCamera.h"

#include "SemperEngine/Core/Input.h"
#include "SemperEngine/Events/EventDispatcher.h"
#include "SemperEngine/Core/Defines.h"
#include "SemperEngine/Log/Log.h"

#include <glm/gtc/quaternion.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#define M_PI 3.14159f


namespace SemperEngine
{
	EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip) :
		m_FOV(fov), m_AspectRatio(aspectRatio),
		m_NearClip(nearClip), m_FarClip(farClip)
	{
		RecalculateCameraMatrices();
	}

	void EditorCamera::OnUpdate(float ts)
	{
		
		ConstRef<Vec2> mouse = Input::GetMousePosition();
		Vec2 delta = (mouse - m_InitialMousePosition) * 0.0015f;
		m_InitialMousePosition = mouse;

		if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
			MousePan(delta);
		else if (Input::IsMouseButtonPressed(Mouse::ButtonLeft))
			MouseRotate(delta);

		RecalculateCameraMatrices();
	}

	void EditorCamera::OnEvent(Event &e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(SE_BIND_EVENT_FN(EditorCamera::OnMouseScroll));
	}

	void EditorCamera::OnImGui()
	{
		ImGui::Begin("Editor camera");

		ImVec2 region = ImGui::GetContentRegionAvail();

		ImGui::Text("Near Clip");
		ImGui::SameLine(100);
		ImGui::SetNextItemWidth(region.x - 100.0f);
		ImGui::DragFloat("##Near Clip", &m_NearClip, 0.1f, 0.0f, 1000.0f);

		ImGui::Text("Far Clip");
		ImGui::SameLine(100);
		ImGui::SetNextItemWidth(region.x - 100.0f);
		ImGui::DragFloat("##Far Clip", &m_FarClip, 0.1f, 0.0f, 1000.0f);

		ImGui::Separator();

		ImGui::Text("Movement Speed");
		ImGui::SameLine(150);
		ImGui::SetNextItemWidth(region.x - 150.0f);
		ImGui::DragFloat("##Movement Speed", &m_MovementSpeed, 0.1f, 0.0f, 10.0f);

		ImGui::Text("Rotation Speed");
		ImGui::SameLine(150);
		ImGui::SetNextItemWidth(region.x - 150.0f);
		ImGui::DragFloat("##Rotation Speed", &m_RotationSpeed, 0.1f, 0.0f, 10.0f);

		ImGui::Text("Zoom Speed");
		ImGui::SameLine(150);
		ImGui::SetNextItemWidth(region.x - 150.0f);
		ImGui::DragFloat("##Zoom Speed", &m_ZoomSpeed, 0.1f, 0.0f, 10.0f);

		ImGui::Separator();

		ImGui::Text("Position: %.2f, %.2f, %.2f", m_Position.x, m_Position.y, m_Position.z);

		ImGui::End();
	}

	void EditorCamera::SetBounds(float width, float height)
	{ 
		m_ViewportWidth = width; 
		m_ViewportHeight = height;

		RecalculateCameraMatrices(); 
	}

	ConstRef<Mat4> EditorCamera::GetViewMatrix() const
	{
		return m_View;
	}
	ConstRef<Mat4> EditorCamera::GetViewProjection() const
	{
		return m_ProjectionView;
	}

	void EditorCamera::RecalculateCameraMatrices()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;

		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);

		m_Position = CalculatePosition();

		glm::quat orientation = GetOrientation();
		m_View = glm::translate(Mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_View = glm::inverse(m_View);

		m_ProjectionView = m_Projection * m_View;
	}

	bool EditorCamera::OnMouseScroll(MouseScrolledEvent &e)
	{
		MouseZoom(e.GetYOffset());

		RecalculateCameraMatrices();

		return false;
	}

	void EditorCamera::MousePan(ConstRef<Vec2> delta)
	{
		m_FocalPoint += -GetRightDirection() * delta.x * m_Distance * m_MovementSpeed;
		m_FocalPoint += GetUpDirection() * delta.y *  m_Distance * m_MovementSpeed;
	}

	void EditorCamera::MouseRotate(ConstRef<Vec2> delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * delta.x * m_RotationSpeed;
		m_Pitch += delta.y * 0.8f;
	}

	void EditorCamera::MouseZoom(float delta)
	{
		m_Distance -= delta * m_ZoomSpeed;
		if (m_Distance < 1.0f)
		{
			m_Distance = 0.5f;
			// m_FocalPoint += GetForwardDirection();
			// m_Distance = 1.0f;
		}
	}

	Vec3 EditorCamera::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), Vec3(0.0f, 1.0f, 0.0f));
	}

	Vec3 EditorCamera::GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), Vec3(1.0f, 0.0f, 0.0f));
	}

	Vec3 EditorCamera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), Vec3(0.0f, 0.0f, -1.0f));
	}

	ConstRef<Vec3> EditorCamera::GetPosition() const
	{
		return m_Position;
	}

	glm::vec3 EditorCamera::CalculatePosition() const
	{
		return m_FocalPoint - GetForwardDirection() * m_Distance;
	}

	glm::quat EditorCamera::GetOrientation() const
	{
		return glm::quat(Vec3(-m_Pitch, -m_Yaw, 0.0f));
	}

	float EditorCamera::GetYaw() const
	{
		return m_Yaw;
	}
	float EditorCamera::GetPitch() const
	{
		return m_Pitch;
	}
}