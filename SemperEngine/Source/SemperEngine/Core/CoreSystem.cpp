#include "Precompiled.h"
#include "CoreSystem.h"

#include "SemperEngine/Log/Log.h"


namespace SemperEngine
{
	void CoreSystem::Initialize()
	{
		Log::Init(true, true);

		SE_CORE_INFO("Initializing Core Engine");
	}
	void CoreSystem::Shutdown()
	{
		SE_CORE_INFO("Shutting down Core Engine");
	}
}