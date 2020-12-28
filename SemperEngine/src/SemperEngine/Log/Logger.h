#pragma once

#include <stdio.h>
#include <string>


namespace SemperEngine
{
    class Logger
    {
	public:
        Logger(const std::string &&name);
        ~Logger() = default;

        template<typename ... Args>
		inline void trace(Args && ... args)
		{
			printf("\033[0;32m");
			printf("[%s][%s] TRACE: ", _GetCurrentTime().c_str(), m_LoggerName.c_str());
			printf(std::forward<Args>(args)...);
			printf("\n");
			printf("\033[0m");
		}
		template<typename ... Args>
		inline void info(Args && ... args)
		{
			printf("\033[0;32m");
			printf("[%s][%s] INFO: ", _GetCurrentTime().c_str(), m_LoggerName.c_str());
			printf(std::forward<Args>(args)...);
			printf("\n");
			printf("\033[0m");
		}
		template<typename ... Args>
		inline void warn(Args && ... args)
		{
			printf("\033[0;33m");
			printf("[%s][%s] WARN: ", _GetCurrentTime().c_str(), m_LoggerName.c_str());
			printf(std::forward<Args>(args)...);
			printf("\n");
			printf("\033[0m");
		}
		template<typename ... Args>
		inline void error(Args && ... args)
		{
			printf("\033[0;31m");
			printf("[%s][%s] ERROR: ", _GetCurrentTime().c_str(), m_LoggerName.c_str());
			printf(std::forward<Args>(args)...);
			printf("\n");
			printf("\033[0m");
		}
		template<typename ... Args>
		inline void critical(Args && ... args)
		{
			printf("\033[1;31m");
			printf("[%s][%s] CRITICAL: ", _GetCurrentTime().c_str(), m_LoggerName.c_str());
			printf(std::forward<Args>(args)...);
			printf("\n");
			printf("\033[0m");
		}

    private:
        std::string _GetCurrentTime();

    private:
        std::string m_LoggerName;
    };
}