#pragma once

#include "SemperEngine/Core/Types.h"


namespace SemperEngine
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(ConstRef<Mat4> projection, ConstRef<Mat4> view);
		Camera(ConstRef<Mat4> projection);

		virtual ~Camera() = default;

		void SetProjection(ConstRef<Mat4> projection);
		void SetView(ConstRef<Mat4> view);

		ConstRef<Mat4> GetProjection() const noexcept;
		ConstRef<Mat4> GetView() const noexcept;

		// Returns projection * view
		ConstRef<Mat4> GetProjectionView() const noexcept;

		// Returns view * projection
		ConstRef<Mat4> GetViewProjection() const noexcept;

	protected:
		Mat4 m_Projection;
		Mat4 m_View;
		Mat4 m_ProjectionView;	// proj * view
		Mat4 m_ViewProjection;	// view * proj
	};
}