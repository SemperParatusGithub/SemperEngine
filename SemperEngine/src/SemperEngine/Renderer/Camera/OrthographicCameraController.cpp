#include "pch.h"
#include "OrthographicCameraController.h"

#include "SemperEngine/Core/Input.h"
#include "SemperEngine/Events/EventDispatcher.h"
#include "SemperEngine/Core/Defines.h"


namespace SemperEngine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, float movementSpeed, float rotationSpeed) : 
		m_Position(0.0f, 0.0f, 0.0f),
		m_Rotation(0.0f),
		m_Zoom(1.0f),
		m_AspectRatio(aspectRatio),
		m_MovementSpeed(5.0f),
		m_RotationSpeed(0.1f),
		m_Camera(-m_AspectRatio * m_Zoom, m_AspectRatio *m_Zoom, -m_Zoom, m_Zoom)
	{
	}

	void OrthographicCameraController::OnUpdate(float deltaTime)
	{
		if (Input::IsKeyPressed(Key::A))
		{
			m_Position.x -= cos(glm::radians(m_Rotation)) * m_MovementSpeed * deltaTime;
			m_Position.y -= sin(glm::radians(m_Rotation)) * m_MovementSpeed * deltaTime;
		}
		else if (Input::IsKeyPressed(Key::D))
		{
			m_Position.x += cos(glm::radians(m_Rotation)) * m_MovementSpeed * deltaTime;
			m_Position.y += sin(glm::radians(m_Rotation)) * m_MovementSpeed * deltaTime;
		}

		if (Input::IsKeyPressed(Key::W))
		{
			m_Position.x += -sin(glm::radians(m_Rotation)) * m_MovementSpeed * deltaTime;
			m_Position.y +=  cos(glm::radians(m_Rotation)) * m_MovementSpeed * deltaTime;
		}
		else if (Input::IsKeyPressed(Key::S))
		{
			m_Position.x -= -sin(glm::radians(m_Rotation)) * m_MovementSpeed * deltaTime;
			m_Position.y -=  cos(glm::radians(m_Rotation)) * m_MovementSpeed * deltaTime;
		}

		m_Camera.SetPosition(m_Position);
	}
	void OrthographicCameraController::OnEvent(Event &e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(SE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
		dispatcher.Dispatch<MouseScrolledEvent>(SE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent &e)
	{
		m_AspectRatio = e.GetWidth()/ e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);

		return false;
	}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e)
	{
		m_Zoom -= e.GetYOffset() * 0.25f;
		m_Zoom = std::max(m_Zoom, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
		
		return false;
	}
}