#include "Precompiled.h"
#include "Log.h"


namespace SemperEngine
{
	SharedPtr<Logger> Log::s_ClientLogger;
	SharedPtr<Logger> Log::s_CoreLogger;

	void Log::Init()
	{
		s_CoreLogger = MakeShared<Logger>("ENGINE");
		s_ClientLogger = MakeShared<Logger>("CLIENT");
	}
}