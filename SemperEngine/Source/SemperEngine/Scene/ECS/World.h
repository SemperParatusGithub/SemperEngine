#pragma once

#include "ECSBase.h"
#include "SemperEngine/Core/Assert.h"

#include <unordered_map>

#include "WorldIterator.h"


namespace SemperEngine
{
	namespace ECS
	{
		class World
		{
		public:
			using Iterator = WorldIterator;

		public:
			Iterator begin()
			{
				return WorldIterator(m_Entities.begin());
			}
			Iterator end()
			{
				return WorldIterator(m_Entities.end());
			}

			EntityHandle CreateEntity()
			{
				static U32 ID = 0;
				ID++;

				m_Entities.emplace(ID, Internal::EntityElem());

				return ID;
			}
			void DestroyEntity(EntityHandle handle)
			{
				m_Entities.erase(handle);
			}

			bool IsValid(EntityHandle handle)
			{
				return m_Entities.find(handle) != m_Entities.end();
			}

			template<typename T, typename ... Args>
			T &Add(EntityHandle handle, Args && ... args)
			{
				if (m_Entities.find(handle) != m_Entities.end())
				{
					auto &entityElem = m_Entities[handle];

					Internal::ComponentContainer<T> *container = new Internal::ComponentContainer<T>(T(std::forward<Args>(args)...));
					entityElem.emplace(Internal::GetTypeIndex<T>(), container);

					return container->data;
				}
				else {
					SE_ASSERT_MSG(false, "Invalid entity handle!");
				}
			}

			template<typename T>
			void Remove(EntityHandle handle)
			{
				if (m_Entities.find(handle) != m_Entities.end())
				{
					auto &entityElem = m_Entities[handle];
					auto found = entityElem.find(Internal::GetTypeIndex<T>());

					if (found != entityElem.end())
						entityElem.erase(found);
				}
				else {
					SE_ASSERT_MSG(false, "Invalid entity handle!");
				}
			}

			template<typename T>
			T &Get(EntityHandle handle)
			{
				if (m_Entities.find(handle) != m_Entities.end())
				{
					auto &entityElem = m_Entities[handle];
					auto found = entityElem.find(Internal::GetTypeIndex<T>());

					if (found != entityElem.end())
						return reinterpret_cast<Internal::ComponentContainer<T> *>(entityElem[Internal::GetTypeIndex<T>()])->data;
					else
						SE_ASSERT_MSG(false, "Component doesn't exist!");
				}
				else {
					SE_ASSERT_MSG(false, "Invalid entity handle!");
				}
			}

			template<typename T>
			bool Has(EntityHandle handle)
			{
				if (m_Entities.find(handle) != m_Entities.end())
				{
					auto &entityElem = m_Entities[handle];
					auto index = Internal::GetTypeIndex<T>();

					return entityElem.find(index) != entityElem.end();
				}
				else {
					SE_ASSERT_MSG(false, "Invalid entity handle!");
				}
			}

			template<typename T1, typename T2, typename ... Types>
			bool Has(EntityHandle handle)
			{
				if (m_Entities.find(handle) != m_Entities.end())
				{
					return Has<T1>(handle) && Has<T2, Types...>(handle);
				}
				else {
					SE_ASSERT_MSG(false, "Invalid entity handle!");
				}
			}

		private:
			std::unordered_map<EntityHandle, Internal::EntityElem> m_Entities;
		};
	}
}