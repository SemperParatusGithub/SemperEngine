#include "Precompiled.h"
#include "Scene.h"

#include "Entity.h"


namespace SemperEngine
{
	Entity Scene::CreateEntity()
	{
		ECS::EntityHandle handle = m_World.CreateEntity();

		return Entity(handle, this);
	}

	ECS::World Scene::GetWorld()
	{
		return m_World;
	}
}