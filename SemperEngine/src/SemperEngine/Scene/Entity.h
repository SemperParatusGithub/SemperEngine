#pragma once
#include "ECS/ECS.h"
#include "Scene.h"

#include "SemperEngine/Core/Assert.h"
#include "Components.h"


namespace SemperEngine
{
	class Entity
	{
	public:
		Entity() = default;

		inline ECS::EntityHandle GetHandle() const 
		{
			return m_Handle;
		}

		template<typename Component, typename ... Args>
		Component &Add(Args && ... args)
		{
			SE_ASSERT_MSG(!Has<Component>(), "Entity already has component");

			Component &component = m_Scene->m_World.Add<Component>(m_Handle, std::forward<Args>(args)...);
			return component;
		}

		template<typename Component>
		void Remove()
		{
			SE_ASSERT_MSG(Has<Component>(), "Component doesn't exist");

			m_Scene->m_World.Remove(m_Handle);
		}

		template<typename Component>
		Component &Get()
		{
			SE_ASSERT_MSG(Has<Component>(), "Component doesn't exist");

			auto &component = m_Scene->m_World.Get<Component>(m_Handle);
			return component;
		}

		template<typename ... Components>
		bool Has()
		{
			return m_Scene->m_World.Has<Components...>(m_Handle);
		}

	private:
		Entity(ECS::EntityHandle entityHandle, Scene *sceneHandle) : 
			m_Handle(entityHandle),
			m_Scene(sceneHandle)
		{
			Add<IdentificationComponent>(IdentificationComponent { "Entity", {} });
		}

	private:
		friend class Scene;

		ECS::EntityHandle m_Handle = ECS::NullEntity;
		Scene *m_Scene = nullptr;
	};
}