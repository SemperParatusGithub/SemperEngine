#pragma once
#include "SemperEngine/Core/Types.h"
#include <iostream>


namespace SemperEngine
{
	struct IdentificationComponent
	{
		IdentificationComponent() = default;
		IdentificationComponent(ConstRef<std::string> name, U64 ID) : 
			name(name), ID(ID) {}

		~IdentificationComponent() = default;

		std::string name = "Entity";
		U64 ID = 0;
	};
}