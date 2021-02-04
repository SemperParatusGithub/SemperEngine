#pragma once
#include "Scene.h"
#include "../../../External/entt/include/entt.hpp"

#include "SemperEngine/Core/Assert.h"


namespace SemperEngine
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity entityHandle, Scene *sceneHandle) :
			m_Handle(entityHandle),
			m_Scene(sceneHandle)
		{
		}

		inline entt::entity GetHandle() const 
		{
			return m_Handle;
		}

		inline Scene *GetScene() const
		{
			return m_Scene;
		}

		template<typename Component, typename ... Args>
		Component &Add(Args && ... args)
		{
			SE_ASSERT_MSG(!Has<Component>(), "Entity already has component");
			
			return m_Scene->GetRegistry().emplace<Component>(m_Handle, std::forward<Args>(args)...);
		}

		template<typename Component>
		void Remove()
		{
			SE_ASSERT_MSG(Has<Component>(), "Component doesn't exist");

			m_Scene->GetRegistry().remove<Component>(m_Handle);
		}

		template<typename Component>
		Component &Get()
		{
			SE_ASSERT_MSG(Has<Component>(), "Component doesn't exist");

			return m_Scene->GetRegistry().get<Component>(m_Handle);
		}

		template<typename Component>
		ConstRef<Component> Get() const
		{
			SE_ASSERT_MSG(Has<Component>(), "Component doesn't exist");

			return m_Scene->GetRegistry().get<Component>();
		}

		template<typename ... Components>
		bool Has()
		{
			return m_Scene->GetRegistry().has<Components...>(m_Handle);
		}

		void Destroy()
		{
			if (m_Handle != entt::null && m_Scene != nullptr)
			{
				m_Scene->GetRegistry().destroy(m_Handle);
				m_Scene = nullptr;
			}
			else {
				SE_ASSERT_MSG(false, "Invalid Entity can't be destroyed!");
			}
		}

		inline operator bool() const
		{ 
			return m_Handle != entt::null && m_Scene != nullptr;
		}

		inline bool operator ==(const Entity other)
		{
			return m_Handle == other.m_Handle && m_Scene == other.m_Scene;
		}
		inline bool operator !=(const Entity other)
		{
			return !this->operator==(other);
		}

	private:
		entt::entity m_Handle { entt::null };
		Scene *m_Scene = nullptr;
	};

	class ScriptableEntity
	{
	public:
		ScriptableEntity() = default;
		virtual ~ScriptableEntity() = default;

		virtual void OnCreate() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnDestroy() {}

		template<typename Component>
		Component &Get() 
		{
			return m_Entity.Get<Component>();
		}

		Entity m_Entity;	// Make me private!
			
	private:
		friend class Scene;
	};
}