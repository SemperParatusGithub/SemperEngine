#pragma once
#include "SemperEngine/Core/Defines.h"
#include "SemperEngine/Core/Types.h"

#include "ConsoleLogger.h"
#include "LogConsole.h"
#include "FileLogger.h"


namespace SemperEngine
{
	class Log
	{
	public:
		static void Init();

		static void EnableAutoFlush(bool enable = true);
		static void EnableEditorLogConsole();

		static void OnEditorLogConsoleGui();

		static void FlushMessageBuffer();

		template<Severity severity, LoggerType loggerType, typename ... Args>
		static inline void LogMessage(Args && ... args)
		{
			char *localBuffer = new char[1024];
			sprintf_s(localBuffer, 1024, std::forward<Args>(args)...);
			std::string message = std::string(localBuffer);

			LogElement element;
			element.time = LogBase::GetTimeAsString();
			element.type = loggerType;
			element.severity = severity;
			element.message = message;

			s_MessageBuffer.push_back(element);

			if (s_AutoFlush)
				FlushMessageBuffer();
		}

	private:
		static std::vector<LogElement> s_MessageBuffer;
		static bool s_AutoFlush;

		static SharedPtr<ConsoleLogger> s_ConsoleLogger;
		static SharedPtr<FileLogger> s_FileLogger;
		static SharedPtr<LogConsole> s_LogConsole;
	};
}


// Logging is only disabled in Production builds

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