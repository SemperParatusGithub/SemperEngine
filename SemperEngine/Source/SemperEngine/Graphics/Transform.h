#pragma once
#include "SemperEngine/Core/Types.h"
#include "SemperEngine/Util/CerealOverloads.h"


namespace SemperEngine
{
	// Rotation is always in radians
	// glm::radians(valueDegrees) or ToRadians(degrees) converts degrees in radians
	// glm::degrees(valueRadians) or ToDegrees(degrees) converts radians in degrees

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

		void Translate(ConstRef<Vec3> offset);
		void Rotate(ConstRef<Vec3> offset);
		void Scale(ConstRef<Vec3> offset);

		ConstRef<Mat4> GetTransform() const noexcept;

		template<typename Archive>
		void save(Archive &archive) const
		{
			archive( cereal::make_nvp("Translation", m_Translation),
					 cereal::make_nvp("Rotation", m_Rotation),
					 cereal::make_nvp("Scale", m_Scale) );
		}
		template<typename Archive>
		void load(Archive &archive)
		{
			archive( cereal::make_nvp("Translation", m_Translation),
					 cereal::make_nvp("Rotation", m_Rotation),
					 cereal::make_nvp("Scale", m_Scale)	);

			Invalidate();
		}

	private:
		void Invalidate();

	private:
		Vec3 m_Translation, m_Rotation, m_Scale;
		Mat4 m_TransformationMatrix;
	};
}