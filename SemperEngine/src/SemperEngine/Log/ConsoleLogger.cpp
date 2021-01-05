#include "Precompiled.h"
#include "ConsoleLogger.h"


namespace SemperEngine
{
	ConsoleLogger::ConsoleLogger()
	{
	}
	ConsoleLogger::~ConsoleLogger()
	{
	}

	void ConsoleLogger::LogMessage(ConstRef<LogElement> element)
	{
		LogBase::SetLogColor(element.severity);

		if (!element.message.empty()) {
			char buf[1024];
			sprintf_s(buf, 1024, "[%s][%s] %s: %s\n", element.time.c_str(), LogBase::LoggerTypeToString(element.type).c_str(),
				LogBase::SeverityToString(element.severity).c_str(), element.message.c_str());
			printf("%s", buf);
		}
		else {
			printf("[WARNING]: Empty message string\n");
		}

		LogBase::ResetLogColor();
	}
}