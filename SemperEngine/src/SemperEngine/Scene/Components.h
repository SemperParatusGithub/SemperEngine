#pragma once
#include "SemperEngine/Core/Types.h"
#include <iostream>

#include "UUID.h"
#include "SemperEngine/Graphics/Transform.h"


namespace SemperEngine
{
	struct IdentificationComponent
	{
		IdentificationComponent() = default;
		IdentificationComponent(ConstRef<std::string> name, UUID ID) : 
			name(name), ID(ID) {}

		~IdentificationComponent() = default;

		std::pair<std::string, UUID> GetNameID()
		{
			return { name, ID };
		}

		std::string name = "Entity";
		UUID ID;
	};

	struct TransformComponent
	{
		Transform transform;

		TransformComponent(ConstRef<Transform> transfom) : 
			transform(transform) {}
		TransformComponent(const TransformComponent &) = default;
		~TransformComponent() = default;

		operator Transform()
		{
			return transform;
		}

		const std::tuple<Vec3, Vec3, Vec3> GetTranslationRotationScale() const
		{
			return std::tuple {
				transform.GetTranslation(),
				transform.GetRotation(),
				transform.GetScale()
			};
		}

		void SetTranslation(ConstRef<Vec3> translation)
		{
			transform.SetTranslation(translation);
		}
		void SetRotation(ConstRef<Vec3> rotation)
		{
			transform.SetRotation(rotation);
		}
		void SetScale(ConstRef<Vec3> scale)
		{
			transform.SetScale(scale);
		}

		ConstRef<Mat4> GetMatrix() const
		{
			return transform.GetTransform();
		}
	};
}