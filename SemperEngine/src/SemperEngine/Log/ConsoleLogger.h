#pragma once

#include "LogBase.h"
#include "SemperEngine/Core/Types.h"


namespace SemperEngine
{
    class ConsoleLogger
    {
	public:
		ConsoleLogger() = default;
        ~ConsoleLogger() = default;

		template<Severity severity>
		inline void LogMessage(ConstRef<std::string> messageString)
		{
			LogBase::SetLogColor(severity);
			
			if (!messageString.empty())
				printf("%s\n", messageString.c_str());
			else
				printf("empty message string\n");
		
			LogBase::ResetLogColor();
		}
    };
}