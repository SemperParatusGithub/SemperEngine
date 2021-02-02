#pragma once

#include "SemperEngine/Core/Types.h"

#include <iostream>	
#include <limits>

#include <type_traits>
#include <typeindex>
#include <typeinfo>

#include <unordered_map>


namespace SemperEngine
{
	namespace ECS
	{
		using EntityHandle = U32;
		constexpr EntityHandle NullEntity = std::numeric_limits<EntityHandle>::max();

		namespace Internal
		{
			using TypeIndex = std::type_index;

			template<typename T>
			TypeIndex GetTypeIndex()
			{
				return std::type_index(typeid(T));
			}

			class BaseComponentContainer
			{
			public:
				virtual ~BaseComponentContainer() = default;
			};

			template<typename T>
			class ComponentContainer : public BaseComponentContainer
			{
			public:
				ComponentContainer() = default;
				ComponentContainer(ConstRef<T> data) :
					data(data)
				{
				}

				T data;
			};

			using EntityElem = std::unordered_map<TypeIndex, BaseComponentContainer *>;
			using EntityIterator = std::unordered_map<EntityHandle, EntityElem>::iterator;
		}
	}
}