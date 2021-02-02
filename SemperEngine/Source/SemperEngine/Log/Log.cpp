#include "Precompiled.h"
#include "Log.h"


namespace SemperEngine
{
	bool Log::s_LogToFile = false;
	bool Log::s_LogToConsole = false;

	std::vector<LogElement> Log::s_TempBuffer;

	SharedPtr<ConsoleLogger> Log::s_ConsoleLogger;
	SharedPtr<FileLogger> Log::s_FileLogger;
	SharedPtr<LogConsole> Log::s_LogConsole;

	void Log::Init(bool logToFile, bool logToConsole)
	{
		s_LogToFile = logToFile;
		s_LogToConsole = logToConsole;

		s_ConsoleLogger = MakeShared<ConsoleLogger>();
		s_FileLogger = MakeShared<FileLogger>("Semper.log");
	}
	void Log::SetLogConsoleInstance(SharedPtr<LogConsole> instance)
	{
		if(s_LogToConsole)
			s_LogConsole = instance;
		else
			LogMessage<Severity::Critical, LoggerType::Core>("Unable to set LogConsole Instance (loggin to LogConsole is switched off)");
	}
}