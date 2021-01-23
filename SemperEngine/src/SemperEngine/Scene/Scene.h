#pragma once
#include "SemperEngine/Core/Types.h"

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

		void OnUpdate(float deltaTime);

		ECS::World &GetWorld();

	private:
		ECS::World m_World;
	};
}