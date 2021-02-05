#pragma once
#include "Camera.h"

#include "SemperEngine/Events/MouseEvent.h"


namespace SemperEngine
{
	class EditorCamera : public Camera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

		bool Is2D();
		bool Is3D();

		bool IsOrthoGraphic();
		bool IsPerspective();

		void Set2D();
		void Set3D();

		void SetOrthographic();
		void SetPerspective();

		void OnUpdate(float ts);
		void OnEvent(Event &e);

		void OnImGui();

		void SetBounds(float width, float height);

		ConstRef<Mat4> GetViewMatrix() const; 
		ConstRef<Mat4> GetViewProjection() const;

		Vec3 GetUpDirection() const;
		Vec3 GetRightDirection() const;
		Vec3 GetForwardDirection() const;
		ConstRef<Vec3> GetPosition() const;
		glm::quat GetOrientation() const;

		float GetYaw() const;
		float GetPitch() const;

	private:
		void RecalculateCameraMatrices();

		bool OnMouseScroll(MouseScrolledEvent &e);

		void MousePan(ConstRef<Vec2> delta);
		void MouseRotate(ConstRef<Vec2> delta);
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition() const;

	private:
		bool m_Is2D = false;
		bool m_Is3D = true;

		bool m_IsOrthographic = false;
		bool m_isPerspective = true;

		float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;

		Vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		Vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };

		Vec2 m_InitialMousePosition = { 0.0f, 0.0f };

		float m_Distance = 10.0f;
		float m_Yaw = 0.0f, m_Pitch = 0.0f;

		float m_MovementSpeed = 1.5f;
		float m_RotationSpeed = 1.0f;
		float m_ZoomSpeed = 0.5f;

		float m_ViewportWidth = 1280, m_ViewportHeight = 720;
	};

}