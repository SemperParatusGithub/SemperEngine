#pragma once
#include "SemperEngine/Core/Types.h"

#include "SemperEngine/Graphics/Camera/OrthographicCamera.h"
#include "SemperEngine/Graphics/Camera/EditorCamera.h"

#include "ECS/ECS.h"
#include "Components.h"


namespace SemperEngine
{
	class Entity;

	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity();
		void DestroyEntity(Entity entity);
		bool IsValid(Entity entity);

		void OnUpdate(float deltaTime, ConstRef<Mat4> projectionView);
		void OnUpdateEditor(float deltaTime, ConstRef<EditorCamera> camera);

		ECS::World &GetWorld();

	private:
		ECS::World m_World;
	};
}