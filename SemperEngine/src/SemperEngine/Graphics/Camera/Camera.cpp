#include "Precompiled.h"
#include "Camera.h"


namespace SemperEngine
{
	Camera::Camera(ConstRef<Mat4> projection, ConstRef<Mat4>view) :
		m_Projection(projection),
		m_View(view),
		m_ProjectionView(projection * view),
		m_ViewProjection(view *projection)
	{
	}
	Camera::Camera(ConstRef<Mat4> projection) :
		m_Projection(projection),
		m_View(Mat4(1.0f)),
		m_ProjectionView(projection),
		m_ViewProjection(projection)
	{
	}

	void Camera::SetProjection(ConstRef<Mat4> projection)
	{
		m_Projection = projection;
	}
	void Camera::SetView(ConstRef<Mat4> view)
	{
		m_View = view;
	}

	ConstRef<Mat4> Camera::GetProjection() const noexcept
	{
		return m_Projection;
	}
	const glm::mat4 &Camera::GetView() const noexcept
	{
		return m_View;
	}

	ConstRef<Mat4> Camera::GetProjectionView() const noexcept
	{
		return m_ProjectionView;
	}
	ConstRef<Mat4> Camera::GetViewProjection() const noexcept
	{
		return m_ViewProjection;
	}
}