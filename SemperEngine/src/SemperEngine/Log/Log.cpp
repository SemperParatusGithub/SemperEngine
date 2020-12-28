#include "Precompiled.h"
#include "Log.h"


namespace SemperEngine
{
	std::shared_ptr<Logger> Log::s_ClientLogger;
	std::shared_ptr<Logger> Log::s_CoreLogger;

	void Log::Init()
	{
		s_CoreLogger = std::make_shared<Logger>("ENGINE");
		s_ClientLogger = std::make_shared<Logger>("CLIENT");
	}
}