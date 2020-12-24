#pragma once
#include "OrthographicCamera.h"

#include"SemperEngine/Events/ApplicationEvent.h"
#include"SemperEngine/Events/MouseEvent.h"


namespace SemperEngine
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, float movementSpeed, float rotationSpeed);
		~OrthographicCameraController() = default;

		inline OrthographicCamera &GetCamera() { return m_Camera; }
		inline const OrthographicCamera &GetCamera() const noexcept { return m_Camera; }

		void OnUpdate(float deltaTime);
		void OnEvent(Event &e);

	private:
		bool OnWindowResize(WindowResizeEvent &e);
		bool OnMouseScrolled(MouseScrolledEvent &e);

		float m_Zoom;
		float m_AspectRatio;
		float m_MovementSpeed;
		float m_RotationSpeed;

		OrthographicCamera m_Camera;

		glm::vec3 m_Position;
		float m_Rotation;
	};
}