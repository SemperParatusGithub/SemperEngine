#include "Precompiled.h"
#include "UUID.h"


namespace SemperEngine
{
	std::random_device					UUID::s_RandomDevice;
	std::mt19937_64						UUID::s_Gen { s_RandomDevice() };
	std::uniform_int_distribution<U64>	UUID::s_UniformDistribution;

	UUID::UUID()
	{
		m_UUID = s_UniformDistribution(s_Gen);
	}
}