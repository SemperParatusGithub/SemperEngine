#include "Precompiled.h"
#include "SceneCamera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


namespace SemperEngine
{
	SceneCamera::SceneCamera()
	{
		RecalculateCameraMatrices();
	}

	void SceneCamera::SetOrthographic()
	{
		m_IsOrthographic = true;
		m_IsPerspective = false;

		RecalculateCameraMatrices();
	}
	void SceneCamera::SetPerspective()
	{
		m_IsPerspective = true;
		m_IsOrthographic = false;

		RecalculateCameraMatrices();
	}
	bool SceneCamera::IsOrthographic() const
	{
		return m_IsOrthographic;
	}
	bool SceneCamera::IsPerspective() const
	{
		return m_IsPerspective;
	}

	void SceneCamera::SetBounds(float width, float height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		RecalculateCameraMatrices();
	}

	void SceneCamera::SetZoom(float zoom)
	{
		m_Zoom = zoom;

		RecalculateCameraMatrices();
	}

	float SceneCamera::GetZoom() const
	{
		return m_Zoom;
	}

	void SceneCamera::SetFOV(float FOV)
	{
		m_FOV = FOV;

		RecalculateCameraMatrices();
	}
	float SceneCamera::GetFOV() const
	{
		return 0.0f;
	}

	void SceneCamera::SetNearClip(float nearClip)
	{
		m_NearClip = nearClip;

		RecalculateCameraMatrices();
	}
	void SceneCamera::SetFarClip(float farClip)
	{
		m_FarClip = farClip;

		RecalculateCameraMatrices();
	}

	float SceneCamera::GetNearClip() const
	{
		return m_NearClip;
	}
	float SceneCamera::GetFarClip() const
	{
		return m_FarClip;
	}

	void SceneCamera::SetPosition(ConstRef<Vec3> position)
	{
		m_Position = position;

		RecalculateCameraMatrices();
	}
	void SceneCamera::SetRotation(ConstRef<Vec3> rotation)
	{
		m_Rotation = rotation;

		RecalculateCameraMatrices();
	}

	ConstRef<Vec3> SceneCamera::GetPosition() const
	{
		return m_Position;
	}
	ConstRef<Vec3> SceneCamera::GetRotation() const
	{
		return m_Rotation;
	}

	void SceneCamera::RecalculateCameraMatrices()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;

		if (m_IsOrthographic)
		{
			m_Projection = glm::ortho(-m_AspectRatio, m_AspectRatio, -1.0f, 1.0f, m_NearClip, m_FarClip);
			m_View = glm::translate(Mat4(1.0f), m_Position);

			if (m_Rotation != Vec3(0.0f))
				m_View *= glm::toMat4(glm::quat(m_Rotation));

			m_View = glm::inverse(m_View);

			m_ProjectionView = m_Projection * m_View;
		}
		else if (m_IsPerspective)
		{
			m_Projection = glm::perspective(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
			m_View = glm::translate(Mat4(1.0f), m_Position);

			if (m_Rotation != Vec3(0.0f))
				m_View *= glm::toMat4(glm::quat(m_Rotation));

			m_View = glm::inverse(m_View);

			m_ProjectionView = m_Projection * m_View;
		}
	}
}