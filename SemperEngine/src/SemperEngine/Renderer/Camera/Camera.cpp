#include "pch.h"
#include "Camera.h"


namespace SemperEngine
{
	Camera::Camera(const glm::mat4 &projection, const glm::mat4 &view) : 
		m_Projection(projection),
		m_View(view),
		m_ProjectionView(projection * view)
	{
	}
	Camera::Camera(const glm::mat4 &projection) : 
		m_Projection(projection),
		m_View(glm::mat4(1.0f)),
		m_ProjectionView(projection) // View is identity
	{
	}

	void Camera::SetProjection(const glm::mat4 &projection)
	{
		m_Projection = projection;
	}
	void Camera::SetView(const glm::mat4 &view)
	{
		m_View = view;
	}

	const glm::mat4 &Camera::GetProjection() const noexcept
	{
		return m_Projection;
	}
	const glm::mat4 &Camera::GetView() const noexcept
	{
		return m_View;
	}

	const glm::mat4 &Camera::GetProjectionView() const noexcept
	{
		return m_ProjectionView;
	}
	const glm::mat4 &Camera::GetViewProjection() const noexcept
	{
		return m_View * m_Projection;
	}
}