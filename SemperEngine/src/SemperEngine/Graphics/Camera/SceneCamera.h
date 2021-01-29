#pragma once
#include "Camera.h"
#include "OrthographicCamera.h"


namespace SemperEngine
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() override = default;

		void SetOrthographic();
		void SetPerspective();

		bool IsOrthographic() const;
		bool IsPerspective() const;

		void SetBounds(float width, float height);

		// ========= Orthographic ==========//
		void SetZoom(float zoom);
		//==================================//

		//========== Perspective ===========//
		void SetFOV(float FOV);
		void SetNearClip(float nearClip);
		void SetFarClip(float farClip);
		//==================================//

		void SetPosition(ConstRef<Vec3> position);
		void SetRotation(ConstRef<Vec3> rotation);

		ConstRef<Vec3> GetPosition() const;
		ConstRef<Vec3> GetRotation() const;

	private:
		void RecalculateCameraMatrices();

	private:
		bool m_IsOrthographic = false;
		bool m_IsPerspective = true;

		Vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		Vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };

		float m_NearClip =  0.1f, m_FarClip = 1000.0f;
		float m_AspectRatio = 1.78f;

		float m_FOV = 45.0f;
		float m_Zoom = 1.0f;

		float m_ViewportWidth = 1280.0f, m_ViewportHeight = 720.0f;
	};
}