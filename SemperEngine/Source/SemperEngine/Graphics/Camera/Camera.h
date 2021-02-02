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

	private:
		void Invalidate();

	protected:
		Mat4 m_Projection = Mat4(1.0f);
		Mat4 m_View = Mat4(1.0f);
		Mat4 m_ProjectionView = Mat4(1.0f);	// projection * view
		Mat4 m_ViewProjection = Mat4(1.0f);	// view * projection
	};
}