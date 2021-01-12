#pragma once

#include "SemperEngine/Core/Types.h"

#include <iostream>	

#include <type_traits>
#include <typeindex>
#include <typeinfo>


namespace SemperEngine
{
	using EntityHandle = U32;

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
}