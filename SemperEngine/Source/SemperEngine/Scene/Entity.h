#pragma once
#include <entt.hpp>

#include "SemperEngine/Scene/Scene.h"
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
		inline Component &Add(Args && ... args)
		{
			SE_ASSERT_MSG(!Has<Component>(), "Entity already has component");
			
			return m_Scene->GetRegistry().emplace<Component>(m_Handle, std::forward<Args>(args)...);
		}

		template<typename Component>
		inline void Remove()
		{
			SE_ASSERT_MSG(Has<Component>(), "Component doesn't exist");

			m_Scene->GetRegistry().remove<Component>(m_Handle);
		}

		template<typename Component>
		inline Component &Get()
		{
			SE_ASSERT_MSG(Has<Component>(), "Component doesn't exist");

			return m_Scene->GetRegistry().get<Component>(m_Handle);
		}

		template<typename Component>
		inline ConstRef<Component> Get() const
		{
			SE_ASSERT_MSG(Has<Component>(), "Component doesn't exist");

			return m_Scene->GetRegistry().get<Component>(m_Handle);
		}

		template<typename ... Components>
		inline bool Has() const
		{
			return m_Scene->GetRegistry().has<Components...>(m_Handle);
		}

		inline void Destroy()
		{
			SE_ASSERT_MSG(m_Handle != entt::null && m_Scene != nullptr, "Invalid Entity");

			m_Scene->GetRegistry().destroy(m_Handle);
			m_Scene = nullptr;
		}

		inline operator bool() const
		{ 
			if (m_Scene && m_Handle != entt::null)
				return m_Scene->GetRegistry().valid(m_Handle);
			else
				return false;
		}
		inline operator entt::entity() const
		{
			return m_Handle;
		}
		inline operator U32() const
		{
			return static_cast<U32>(m_Handle);
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

		inline virtual void OnCreate() {}
		inline virtual void OnUpdate(float deltaTime) {}
		inline virtual void OnDestroy() {}
		inline virtual void OnGui() {}

		template<typename Component>
		inline Component &Get() 
		{
			return m_Entity.Get<Component>();
		}
		template<typename ... Components>
		inline bool Has() const
		{
			return m_Entity.Has<Components...>();
		}
			
	private:
		friend class Scene;
		Entity m_Entity;
	};
}