#pragma once
#include "SemperEngine/Core/Types.h"

#include "ECS/ECS.h"


namespace SemperEngine
{
	class Entity;

	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity();
		void RemoveEntity(Entity entity);

		ECS::World GetWorld();

		void OnImGuiRender();

	private:
		friend class Entity;

	private:
		ECS::World m_World;
		ECS::EntityHandle m_ActiveEntityHandle = ECS::NullEntity;
	};
}