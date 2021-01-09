#pragma once
#include <time.h>
#include <sstream>


namespace SemperEngine
{
	enum class LoggerType
	{
		Core = 0,
		Client
	};

	enum class Severity
	{
		Info = 0,
		Warn,
		Error,
		Critical
	};

	struct LogElement
	{
		std::string time;
		LoggerType type;
		Severity severity;
		std::string message;
	};

	namespace ColorCodes
	{
		static const char *Reset = "\033[0m";			// Switch back to default colors
		
		static const char *Green = "\033[0;32m";		// Info
		static const char *Yellow = "\033[0;33m";		// Warn
		static const char *Red = "\033[0;31m";			// Error
		static const char *LightRed = "\033[1;31m";		// Critical
	}

	class LogBase
	{
	public:
		static inline void SetLogColor(Severity severity)
		{
			switch (severity)
			{
				case Severity::Info:		printf(ColorCodes::Green);		break;
				case Severity::Warn:		printf(ColorCodes::Yellow);		break;
				case Severity::Error:		printf(ColorCodes::Red);		break;
				case Severity::Critical:	printf(ColorCodes::LightRed);	break;

				default: printf(ColorCodes::Reset);							break;
			}
		}

		static inline std::string SeverityToString(Severity severity)
		{
			switch (severity)
			{
				case Severity::Info:		return "Info"; 		break;
				case Severity::Warn:		return "Warn";		break;
				case Severity::Error:		return "Error"; 	break;
				case Severity::Critical:	return "Critical";	break;

				default: return "Unknown Severity";				break;
			}
		}

		static inline std::string LoggerTypeToString(LoggerType type)
		{
			switch (type)
			{
				case LoggerType::Core:		return "Core"; 		break;
				case LoggerType::Client:	return "Client";	break;

				default: return "Unknown LoggerType";			break;
			}
		}

		static inline void ResetLogColor()
		{
			printf(ColorCodes::Reset);
		}

		static inline std::string GetTimeAsString()
		{
			time_t theTime = time(nullptr);
			struct tm aTime;
			localtime_s(&aTime, &theTime);

			int hour = aTime.tm_hour;
			int min = aTime.tm_min;
			int sec = aTime.tm_sec;

			std::stringstream ss;

			ss << ((hour < 10) ? "0" : "") << hour << ":";
			ss << ((min < 10) ? "0" : "") << min << ":";
			ss << ((sec < 10) ? "0" : "") << sec;

			return ss.str();
		}
	};
}