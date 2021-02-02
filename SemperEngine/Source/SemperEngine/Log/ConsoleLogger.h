#pragma once
#include "SemperEngine/Core/Types.h"
#include "LogBase.h"


namespace SemperEngine
{
    class ConsoleLogger
    {
	public:
		ConsoleLogger();
		~ConsoleLogger();

		void LogMessage(ConstRef<LogElement> element);
    };
}