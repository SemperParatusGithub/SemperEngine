#include "Precompiled.h"
#include "Transform.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


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
		m_Rotation.x = rotation.x >= glm::radians(360.0f) ? rotation.x - glm::radians(360.0f) : rotation.x;
		m_Rotation.y = rotation.y >= glm::radians(360.0f) ? rotation.y - glm::radians(360.0f) : rotation.y;
		m_Rotation.z = rotation.z >= glm::radians(360.0f) ? rotation.z - glm::radians(360.0f) : rotation.z;

		Invalidate();
	}
	void Transform::SetScale(ConstRef<Vec3> scale)
	{
		m_Scale = scale;

		Invalidate();
	}

	void Transform::Translate(ConstRef<Vec3> offset)
	{
		m_Translation += offset;

		Invalidate();
	}
	void Transform::Rotate(ConstRef<Vec3> offset)
	{
		m_Rotation += offset;

		m_Rotation.x = m_Rotation.x >= glm::radians(360.0f) ? m_Rotation.x - glm::radians(360.0f) : m_Rotation.x;
		m_Rotation.y = m_Rotation.y >= glm::radians(360.0f) ? m_Rotation.y - glm::radians(360.0f) : m_Rotation.y;
		m_Rotation.z = m_Rotation.z >= glm::radians(360.0f) ? m_Rotation.z - glm::radians(360.0f) : m_Rotation.z;

		Invalidate();
	}
	void Transform::Scale(ConstRef<Vec3> offset)
	{
		m_Scale += offset;

		Invalidate();
	}

	ConstRef<Mat4> Transform::GetTransform() const noexcept
	{
		return m_TransformationMatrix;
	}

	void Transform::Invalidate()
	{
		m_TransformationMatrix = Mat4(1.0f);

		m_TransformationMatrix *= glm::translate(Mat4(1.0f), m_Translation);

		if (m_Rotation != Vec3(0.0f))
			m_TransformationMatrix *= glm::toMat4(glm::quat(m_Rotation));

		m_TransformationMatrix *= glm::scale(Mat4(1.0f), m_Scale);
	}
}