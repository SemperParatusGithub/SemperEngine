#pragma once
#include "ECS/ECS.h"
#include "Scene.h"

#include "SemperEngine/Core/Assert.h"


namespace SemperEngine
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(ECS::EntityHandle entityHandle, Scene *sceneHandle) :
			m_Handle(entityHandle),
			m_Scene(sceneHandle)
		{
		}

		inline ECS::EntityHandle GetHandle() const 
		{
			return m_Handle;
		}

		template<typename Component, typename ... Args>
		Component &Add(Args && ... args)
		{
			SE_ASSERT_MSG(!Has<Component>(), "Entity already has component");

			Component &component = m_Scene->GetWorld().Add<Component>(m_Handle, std::forward<Args>(args)...);
			return component;
		}

		template<typename Component>
		void Remove()
		{
			SE_ASSERT_MSG(Has<Component>(), "Component doesn't exist");

			m_Scene->GetWorld().Remove<Component>(m_Handle);
		}

		template<typename Component>
		Component &Get()
		{
			SE_ASSERT_MSG(Has<Component>(), "Component doesn't exist");

			auto &component = m_Scene->GetWorld().Get<Component>(m_Handle);
			return component;
		}

		template<typename ... Components>
		bool Has()
		{
			return m_Scene->GetWorld().Has<Components...>(m_Handle);
		}

		void Destroy()
		{
			if (m_Handle != ECS::NullEntity) {
				m_Scene->GetWorld().DestroyEntity(m_Handle);
				m_Handle = ECS::NullEntity;
				m_Scene = nullptr;
			}
			else
				SE_ASSERT_MSG(false, "Invalid Entity can't be destroyed!");
		}

		operator bool() 
		{ 
			if (m_Handle != ECS::NullEntity && m_Scene != nullptr)
			{
				if (m_Scene->IsValid(*this))
					return true;
			}
			else {
				return false;
			}
			return false;
		}

		bool operator ==(const Entity other)
		{
			return m_Handle == other.m_Handle;
		}
		bool operator !=(const Entity other)
		{
			return !this->operator==(other);
		}

	private:
		ECS::EntityHandle m_Handle = ECS::NullEntity;
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