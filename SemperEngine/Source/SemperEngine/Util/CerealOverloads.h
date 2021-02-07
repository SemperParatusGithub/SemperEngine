#pragma once

#include <cereal/cereal.hpp>
#include "SemperEngine/Core/Types.h"

// Built in overloads
#include <cereal/types/array.hpp>
#include <cereal/types/atomic.hpp>
#include <cereal/types/bitset.hpp>
#include <cereal/types/chrono.hpp>
#include <cereal/types/complex.hpp>

// Overload for glm vectors
namespace glm
{
	template<typename Archive>
	void serialize(Archive &archive, glm::vec2 &vector)
	{
		archive( cereal::make_nvp("x", vector.x),
				 cereal::make_nvp("y", vector.y) );
	}
	template<typename Archive>
	void serialize(Archive &archive, glm::vec3 &vector)
	{
		archive( cereal::make_nvp("x", vector.x),
				 cereal::make_nvp("y", vector.y),
				 cereal::make_nvp("z", vector.z) );
	}
	template<typename Archive>
	void serialize(Archive &archive, glm::vec4 &vector)
	{
		archive( cereal::make_nvp("x", vector.x),
				 cereal::make_nvp("y", vector.y),
				 cereal::make_nvp("z", vector.z),
				 cereal::make_nvp("w", vector.w) );
	}
}