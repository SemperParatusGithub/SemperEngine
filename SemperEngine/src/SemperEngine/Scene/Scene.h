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

		ECS::World GetWorld();

	private:
		friend class Entity;

		ECS::World m_World;
	};
}