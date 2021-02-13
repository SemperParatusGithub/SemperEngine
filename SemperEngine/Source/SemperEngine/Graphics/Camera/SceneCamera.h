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
		float GetZoom() const;
		//==================================//

		//========== Perspective ===========//
		void SetFOV(float FOV);
		float GetFOV() const;
		//==================================//

		void SetNearClip(float nearClip);
		void SetFarClip(float farClip);

		float GetNearClip() const;
		float GetFarClip() const;

		void SetPosition(ConstRef<Vec3> position);
		void SetRotation(ConstRef<Vec3> rotation);

		ConstRef<Vec3> GetPosition() const;
		ConstRef<Vec3> GetRotation() const;

		template<typename Archive>
		void save(Archive &archive) const
		{
			archive( cereal::make_nvp("IsOrthographic", m_IsOrthographic),
					 cereal::make_nvp("IsPerspective", m_IsPerspective),
					 cereal::make_nvp("Position", m_Position),
					 cereal::make_nvp("Rotation", m_Rotation),
					 cereal::make_nvp("NearClip", m_NearClip),
					 cereal::make_nvp("FarClip", m_FarClip),
					 cereal::make_nvp("AspectRation", m_AspectRatio),
					 cereal::make_nvp("FOV", m_FOV),
					 cereal::make_nvp("Zoom", m_Zoom),
					 cereal::make_nvp("ViewportWidth", m_ViewportWidth),
					 cereal::make_nvp("ViewportHeight", m_ViewportHeight) );
		}
		template<typename Archive>
		void load(Archive &archive)
		{
			archive( cereal::make_nvp("IsOrthographic", m_IsOrthographic),
					 cereal::make_nvp("IsPerspective", m_IsPerspective),
					 cereal::make_nvp("Position", m_Position),
					 cereal::make_nvp("Rotation", m_Rotation),
					 cereal::make_nvp("NearClip", m_NearClip),
					 cereal::make_nvp("FarClip", m_FarClip),
					 cereal::make_nvp("AspectRation", m_AspectRatio),
					 cereal::make_nvp("FOV", m_FOV),
					 cereal::make_nvp("Zoom", m_Zoom),
					 cereal::make_nvp("ViewportWidth", m_ViewportWidth),
					 cereal::make_nvp("ViewportHeight", m_ViewportHeight) );

			RecalculateCameraMatrices();
		}

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