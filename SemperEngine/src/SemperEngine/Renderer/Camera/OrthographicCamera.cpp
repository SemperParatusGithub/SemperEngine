#include "pch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>


namespace SemperEngine
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	{
		m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_View = glm::mat4(1.0f);

		m_ProjectionView = m_Projection * m_View;

		m_Position = { 0.0f, 0.0f, 0.0f };
		m_Rotation = 0.0f;
	}
	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

		m_ProjectionView = m_Projection * m_View;
	}

	void OrthographicCamera::SetPosition(const glm::vec3 &position)
	{
		m_Position = position;

		Invalidate();
	}
	void OrthographicCamera::SetRotation(float rotation)
	{
		m_Rotation = rotation;

		Invalidate();
	}

	const glm::vec3 &OrthographicCamera::GetPosition() const
	{
		return m_Position;
	}
	float OrthographicCamera::GetRotation() const
	{
		return m_Rotation;
	}

	void OrthographicCamera::Invalidate()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_View = glm::inverse(transform);
		m_ProjectionView = m_Projection * m_View;
	}
}