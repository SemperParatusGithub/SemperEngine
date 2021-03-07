#include "Precompiled.h"
#include "Log.h"


namespace SemperEngine
{
	std::vector<LogElement> Log::s_MessageBuffer;
	bool Log::s_AutoFlush = false;

	SharedPtr<ConsoleLogger> Log::s_ConsoleLogger;
	SharedPtr<FileLogger> Log::s_FileLogger;
	SharedPtr<LogConsole> Log::s_LogConsole;

	void Log::Init()
	{
		s_ConsoleLogger = MakeShared<ConsoleLogger>();
		s_FileLogger = MakeShared<FileLogger>("Semper.log");
	}
	void Log::EnableAutoFlush(bool enable)
	{
		s_AutoFlush = enable;
	}
	void Log::EnableEditorLogConsole()
	{
		s_LogConsole = MakeShared<LogConsole>();
	}
	void Log::OnEditorLogConsoleGui()
	{
		if(s_LogConsole)
			s_LogConsole->OnImGuiRender();
	}
	void Log::FlushMessageBuffer()
	{
		for (const auto &element : s_MessageBuffer)
		{
			// Log to command window
			s_ConsoleLogger->LogMessage(element);

			// Log to logFile
			s_FileLogger->LogMessage(element);

			// Log to editor console
			if (s_LogConsole)
				s_LogConsole->LogMessage(element);
		}

		s_FileLogger->Flush();

		s_MessageBuffer.clear();
	}
}