#pragma once
#include "Camera.h"


namespace SemperEngine
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		virtual ~OrthographicCamera() override = default;

		void SetProjection(float left, float right, float bottom, float top);

		void SetPosition(const glm::vec3 &position);
		void SetRotation(float rotation); // Degrees

		const glm::vec3 &GetPosition() const;
		float GetRotation() const;	// Degrees

	private:
		void Invalidate();

	private:
		glm::vec3 m_Position;
		float m_Rotation;
	};
}