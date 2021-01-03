#pragma once

#include "LogBase.h"


namespace SemperEngine
{
	enum LoggerType
	{
		Core = 0,
		Client
	};

    class Logger
    {
	public:
        Logger(const std::string &name);
        ~Logger() = default;

		template<Severity severity, typename ... Args>
		inline void LogMessage(Args && ... args)
		{
			LogBase::SetLogColor(severity);
			
			printf("[%s][%s] %s: ", LogBase::GetTimeAsString().c_str(), m_LoggerName.c_str(), LogBase::SeverityToString(severity).c_str());
			printf(std::forward<Args>(args)...);
			printf("\n");
		
			LogBase::ResetLogColor();
		}

    private:
        std::string m_LoggerName;
    };
}