#pragma once
#include "SemperEngine/Core/Types.h"


namespace SemperEngine
{
	class Transform
	{
	public:
		Transform();
		Transform(ConstRef<Vec3> translation, ConstRef<Vec3> rotation, ConstRef<Vec3> scale);

		ConstRef<Vec3> GetTranslation() const noexcept;
		ConstRef<Vec3> GetRotation() const noexcept;
		ConstRef<Vec3> GetScale() const noexcept;

		void SetTranslation(ConstRef<Vec3> translation);
		void SetRotation(ConstRef<Vec3> rotation);
		void SetScale(ConstRef<Vec3> scale);

		ConstRef<Mat4> GetTransform() const noexcept;

	private:
		void Invalidate();

	private:
		Vec3 m_Translation, m_Rotation, m_Scale;
		Mat4 m_TransformationMatrix;
	};
}