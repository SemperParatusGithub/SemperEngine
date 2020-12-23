#pragma once

#include <glm/glm.hpp>


namespace SemperEngine
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4 &projection, const glm::mat4 &view);
		Camera(const glm::mat4 &projection);

		virtual ~Camera() = default;

		void SetProjection(const glm::mat4 &projection);
		void SetView(const glm::mat4 &view);

		const glm::mat4 &GetProjection() const noexcept;
		const glm::mat4 &GetView() const noexcept;

		// Returns projection * view
		const glm::mat4 &GetProjectionView() const noexcept;

		// Returns view * projection
		const glm::mat4 &GetViewProjection() const noexcept;

	protected:
		glm::mat4 m_Projection;
		glm::mat4 m_View;
		glm::mat4 m_ProjectionView; // proj * view
	};
}