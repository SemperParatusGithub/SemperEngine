#pragma once

#include "ConsoleLogger.h"
#include "FileLogger.h"

#include "SemperEngine/Core/Defines.h"
#include "SemperEngine/Core/Types.h"

#include <sstream>


namespace SemperEngine
{
	class Log
	{
	public:
		static void Init(bool logToFile, bool logToConsole);

		template<Severity severity, LoggerType loggerType, typename ... Args>
		static void LogMessage(Args && ... args)
		{
			std::stringstream messageStream;

			std::string time = "[" + LogBase::GetTimeAsString() + "]";

			std::string loggerName = loggerType == LoggerType::Core ? "[CORE]" : "[CLIENT]";

			std::string severityString = LogBase::SeverityToString(severity) + ": ";

			char *localBuffer = new char[256];
			sprintf_s(localBuffer, 255, std::forward<Args>(args)...);
			std::string message = std::string(localBuffer);

			messageStream << time;
			messageStream << loggerName;
			messageStream << severityString;
			messageStream << message;

			s_ConsoleLogger->LogMessage<severity>(messageStream.str());

			if (s_LogToFile) {
				s_FileLogger->LogMessage(messageStream.str());
				s_FileLogger->Flush();
			}

			// TODO Log to console (Editor)
		}

	private:
		static bool s_LogToFile;
		static bool s_LogToConsole;

		static SharedPtr<ConsoleLogger> s_ConsoleLogger;
		static SharedPtr<FileLogger> s_FileLogger;
	};
}


// Logging is only disabled in distribution builds

#if defined(SE_DEBUG) || defined(SE_RELEASE)
	
	#define SE_CORE_INFO(...)		::SemperEngine::Log::LogMessage<SemperEngine::Severity::Info, SemperEngine::LoggerType::Core>(__VA_ARGS__);
	#define SE_CORE_WARN(...)		::SemperEngine::Log::LogMessage<SemperEngine::Severity::Warn, SemperEngine::LoggerType::Core>(__VA_ARGS__);
	#define SE_CORE_ERROR(...)		::SemperEngine::Log::LogMessage<SemperEngine::Severity::Error, SemperEngine::LoggerType::Core>(__VA_ARGS__);
	#define SE_CORE_CRITICAL(...)	::SemperEngine::Log::LogMessage<SemperEngine::Severity::Critical, SemperEngine::LoggerType::Core>(__VA_ARGS__);
	
	#define SE_CLIENT_INFO(...)		::SemperEngine::Log::LogMessage<SemperEngine::Severity::Info, SemperEngine::LoggerType::Client>(__VA_ARGS__);
	#define SE_CLIENT_WARN(...)		::SemperEngine::Log::LogMessage<SemperEngine::Severity::Warn, SemperEngine::LoggerType::Client>(__VA_ARGS__);
	#define SE_CLIENT_ERROR(...)	::SemperEngine::Log::LogMessage<SemperEngine::Severity::Error, SemperEngine::LoggerType::Client>(__VA_ARGS__);
	#define SE_CLIENT_CRITICAL(...)	::SemperEngine::Log::LogMessage<SemperEngine::Severity::Critical, SemperEngine::LoggerType::Client>(__VA_ARGS__);

#else

	#define SE_CORE_INFO(...)		
	#define SE_CORE_WARN(...)		
	#define SE_CORE_ERROR(...)		
	#define SE_CORE_CRITICAL(...)	
	
	#define SE_CLIENT_INFO(...)		
	#define SE_CLIENT_WARN(...)		
	#define SE_CLIENT_ERROR(...)	
	#define SE_CLIENT_CRITICAL(...)

#endif