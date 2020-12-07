#include "pch.h"
#include "Logger.h"

#include <time.h>
#include <sstream>

namespace SemperEngine
{

    Logger::Logger(const std::string &&name) :
        m_LoggerName(name)
    {
    }

    std::string Logger::_GetCurrentTime()
    {
        time_t theTime = time(nullptr);
        struct tm *aTime = localtime(&theTime);

        int hour = aTime->tm_hour;
        int min  = aTime->tm_min;
        int sec  = aTime->tm_sec;

        std::stringstream ss;
        ss << hour << ":" << min << ":" << sec;
        
        return ss.str();
    }
}