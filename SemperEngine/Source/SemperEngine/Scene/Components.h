#pragma once
#include "SemperEngine/Core/Types.h"
 
#include "UUID.h"
#include "Entity.h"

#include "SemperEngine/Graphics/Transform.h"
#include "SemperEngine/Graphics/Sprite.h"

#include "SemperEngine/Graphics/Camera/SceneCamera.h"

#define ALL_COMPONENTS IdentificationComponent, TransformComponent, SpriteComponent, \
							SceneCameraComponent, NativeScriptComponent


namespace SemperEngine
{
	struct IdentificationComponent
	{
		std::string name = "Entity";
		UUID ID;

		IdentificationComponent() = default;
		IdentificationComponent(ConstRef<std::string> name, UUID ID) : 
			name(name), ID(ID) {}

		~IdentificationComponent() = default;

		std::pair<std::string, UUID> GetNameID()
		{
			return { name, ID };
		}

		template<typename Archive>
		void save(Archive &archive) const
		{
			archive( cereal::make_nvp("Name", name),
					 cereal::make_nvp("UUID", static_cast<U64>(ID)) );
		}
		template<typename Archive>
		void load(Archive &archive)
		{
			archive( cereal::make_nvp("Name", name),
					 cereal::make_nvp("UUID", static_cast<U64>(ID)) );
		}
	};

	struct TransformComponent
	{
		Transform transform;

		TransformComponent() = default;
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

		template<typename Archive>
		void save(Archive &archive) const
		{
			archive( cereal::make_nvp("Transform", transform) );
		}
		template<typename Archive>
		void load(Archive &archive)
		{
			archive( cereal::make_nvp("Transform", transform) );
		}
	};

	struct SpriteComponent
	{
		Sprite sprite;
		int xIndex = 0, yIndex = 0;
		int cellWidth = 1024, cellHeight = 1024;

		SpriteComponent() = default;
		SpriteComponent(ConstRef<SpriteComponent>) = default;

		~SpriteComponent() = default;

		void SetTexture(SharedPtr<Texture2D> texture)
		{
			sprite.SetTexture(texture);
		}
		SharedPtr<Texture2D> GetTexture() const
		{
			return sprite.GetTexture();
		}
		void SetTextureSheet(SharedPtr<Texture2D> texture, ConstRef<Vec2> index, ConstRef<Vec2> cellSize)
		{
			sprite.SetSpriteSheet(texture, index, cellSize);
		}

		void SetColor(ConstRef<Vec4> color)
		{
			sprite.SetColor(color);
		}
		ConstRef<Vec4> GetColor() const
		{
			return sprite.GetColor();
		}
	};

	struct SceneCameraComponent
	{
		SceneCamera camera;
		bool primary = false;

		SceneCameraComponent() = default;
		SceneCameraComponent(ConstRef<SceneCameraComponent>) = default;

		~SceneCameraComponent() = default;

		void SetPosition(ConstRef<Vec3> position)
		{
			camera.SetPosition(position);
		}
		void SetRotation(ConstRef<Vec3> rotation)
		{
			camera.SetRotation(rotation);
		}

		ConstRef<Vec3> GetPosition() const
		{
			return camera.GetPosition();
		}
		ConstRef<Vec3> GetRotation() const
		{
			return camera.GetRotation();
		}

		ConstRef<Mat4> GetProjectionViewMatrix()
		{
			return camera.GetProjectionView();
		}

		void SetBounds(float width, float height)
		{
			camera.SetBounds(width, height);
		}
	};

	struct NativeScriptComponent
	{
		ScriptableEntity *instance;

		ScriptableEntity*(*CreateInstance)();
		void(*DestroyInstance)(NativeScriptComponent *);

		template<typename Script>
		void AttachScript()
		{
			CreateInstance = []() {
				return static_cast<ScriptableEntity *>(new Script());
			};
			DestroyInstance = [](NativeScripComponent *nsc) {
				delete nsc->instance; 
				nsc->instance = nullptr;
			};
		}
		void OnCreate()
		{
			instance->OnCreate();
		}
		void OnUpdate(float deltaTime)
		{
			instance->OnUpdate(deltaTime);
		}
		void OnDestroy()
		{
			instance->OnDestroy();
		}
	};
}