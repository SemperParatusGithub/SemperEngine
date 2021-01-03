#pragma once

#include "Logger.h"

#include "SemperEngine/Core/Defines.h"
#include "SemperEngine/Core/Types.h"


namespace SemperEngine
{
	class Log
	{
	public:
		static void Init();

		template<Severity severity, LoggerType loggerType, typename ... Args>
		static void LogMessage(Args && ... args)
		{
			if(loggerType == LoggerType::Core)
				s_CoreLogger->LogMessage<severity>(std::forward<Args>(args)...);

			else if(loggerType == LoggerType::Client)
				s_ClientLogger->LogMessage<severity>(std::forward<Args>(args)...);

			else
				s_CoreLogger->LogMessage<Severity::Warn>("Can't log Message - Unknown Logger");

			// TODO Log to console (Editor)
			// Log to file
		}

	private:
		static SharedPtr<Logger> s_CoreLogger;
		static SharedPtr<Logger> s_ClientLogger;
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