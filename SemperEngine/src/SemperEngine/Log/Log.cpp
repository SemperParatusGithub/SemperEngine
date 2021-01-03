#include "Precompiled.h"
#include "Log.h"


namespace SemperEngine
{
	bool Log::s_LogToFile = false;
	bool Log::s_LogToConsole = false;

	SharedPtr<ConsoleLogger> Log::s_ConsoleLogger;
	SharedPtr<FileLogger> Log::s_FileLogger;

	void Log::Init(bool logToFile, bool logToConsole)
	{
		s_LogToFile = logToFile;
		s_LogToConsole = logToConsole;

		s_ConsoleLogger = MakeShared<ConsoleLogger>();
		s_FileLogger = MakeShared<FileLogger>("Semper.log");
	}
}