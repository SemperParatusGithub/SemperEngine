#pragma once

#include "Logger.h"
#include <memory>

#include "SemperEngine/Core/Defines.h"

namespace SemperEngine
{

	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<Logger> &GetCoreLogger()   { return s_CoreLogger;   }
		static std::shared_ptr<Logger> &GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<Logger> s_CoreLogger;
		static std::shared_ptr<Logger> s_ClientLogger;
	};

}

#if defined(SE_DEBUG) || defined(SE_RELEASE)
	
	#define SE_CORE_TRACE(...)		::SemperEngine::Log::GetCoreLogger()->trace(__VA_ARGS__);
	#define SE_CORE_INFO(...)		::SemperEngine::Log::GetCoreLogger()->info(__VA_ARGS__);
	#define SE_CORE_WARN(...)		::SemperEngine::Log::GetCoreLogger()->warn(__VA_ARGS__);
	#define SE_CORE_ERROR(...)		::SemperEngine::Log::GetCoreLogger()->error(__VA_ARGS__);
	#define SE_CORE_CRITICAL(...)	::SemperEngine::Log::GetCoreLogger()->critical(__VA_ARGS__);
	
	#define SE_CLIENT_TRACE(...)	::SemperEngine::Log::GetClientLogger()->trace(__VA_ARGS__);
	#define SE_CLIENT_INFO(...)		::SemperEngine::Log::GetClientLogger()->info(__VA_ARGS__);
	#define SE_CLIENT_WARN(...)		::SemperEngine::Log::GetClientLogger()->warn(__VA_ARGS__);
	#define SE_CLIENT_ERROR(...)	::SemperEngine::Log::GetClientLogger()->error(__VA_ARGS__);
	#define SE_CLIENT_CRITICAL(...)	::SemperEngine::Log::GetClientLogger()->critical(__VA_ARGS__);

#else

	#define SE_CORE_TRACE(...)		
	#define SE_CORE_INFO(...)		
	#define SE_CORE_WARN(...)		
	#define SE_CORE_ERROR(...)		
	#define SE_CORE_CRITICAL(...)	
	
	#define SE_CLIENT_TRACE(...)	
	#define SE_CLIENT_INFO(...)		
	#define SE_CLIENT_WARN(...)		
	#define SE_CLIENT_ERROR(...)	
	#define SE_CLIENT_CRITICAL(...)

#endif
