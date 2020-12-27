#include "pch.h"
#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>


namespace SemperEngine
{
	Transform::Transform() : 
		m_Translation(Vec3(0.0f)),
		m_Rotation(Vec3(0.0f)),
		m_Scale(Vec3(1.0f))
	{
		Invalidate();
	}

	Transform::Transform(ConstRef<Vec3> translation, ConstRef<Vec3> rotation, ConstRef<Vec3> scale) : 
		m_Translation(translation),
		m_Rotation(rotation),
		m_Scale(scale)
	{
		Invalidate();
	}

	ConstRef<Vec3> Transform::GetTranslation() const noexcept
	{
		return m_Translation;
	}
	ConstRef<Vec3> Transform::GetRotation() const noexcept
	{
		return m_Rotation;
	}
	ConstRef<Vec3> Transform::GetScale() const noexcept
	{
		return m_Scale;
	}

	void Transform::SetTranslation(ConstRef<Vec3> translation)
	{
		m_Translation = translation;

		Invalidate();
	}
	void Transform::SetRotation(ConstRef<Vec3> rotation)
	{
		m_Rotation = rotation;

		Invalidate();
	}
	void Transform::SetScale(ConstRef<Vec3> scale)
	{
		m_Scale = scale;

		Invalidate();
	}

	ConstRef<Mat4> Transform::GetTransform() const noexcept
	{
		return m_TransformationMatrix;
	}

	void Transform::Invalidate()
	{
		m_TransformationMatrix = Mat4(1.0f);

		if(m_Translation != Vec3(0.0f))
			m_TransformationMatrix *= glm::translate(Mat4(1.0f), m_Translation);

		if (m_Rotation.x != 0.0f)
			m_TransformationMatrix *= glm::rotate(Mat4(1.0f), m_Rotation.x, Vec3(1.0f, 0.0f, 0.0f));

		if (m_Rotation.y != 0.0f)
			m_TransformationMatrix *= glm::rotate(Mat4(1.0f), m_Rotation.y, Vec3(0.0f, 1.0f, 0.0f));

		if (m_Rotation.z != 0.0f)
			m_TransformationMatrix *= glm::rotate(Mat4(1.0f), m_Rotation.z, Vec3(0.0f, 0.0f, 1.0f));

		if(m_Scale != Vec3(1.0f))
			m_TransformationMatrix *= glm::scale(Mat4(1.0f), m_Scale);
	}
}