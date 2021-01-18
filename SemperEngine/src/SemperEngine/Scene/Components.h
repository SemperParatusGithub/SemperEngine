#pragma once
#include "SemperEngine/Core/Types.h"
#include <iostream>

#include "UUID.h"
#include "SemperEngine/Graphics/Transform.h"


namespace SemperEngine
{
	struct IdentificationComponent
	{
		IdentificationComponent() = default;
		IdentificationComponent(ConstRef<std::string> name, UUID ID) : 
			name(name), ID(ID) {}

		~IdentificationComponent() = default;

		std::pair<std::string, UUID> GetNameID()
		{
			return { name, ID };
		}

		std::string name = "Entity";
		UUID ID;
	};
}