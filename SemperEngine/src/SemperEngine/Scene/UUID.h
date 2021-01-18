#pragma once
#include "SemperEngine/Core/Types.h"

#include <random>


namespace SemperEngine
{
	class UUID
	{
	public:
		UUID();
		UUID(const UUID &) = default;
		~UUID() = default;

	private:
		U64 m_UUID;

		static std::random_device					s_RandomDevice;
		static std::mt19937_64						s_Gen;
		static std::uniform_int_distribution<U64>	s_UniformDistribution;
	};
}