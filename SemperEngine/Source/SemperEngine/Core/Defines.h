#pragma once

#include <iostream>

#include "Platforms.h"


#ifdef SE_DEBUG

	#if defined(SE_PLATFORM_WINDOWS)
		#define SE_DEBUGBREAK __debugbreak()

	#elif defined(SE_PLATFORM_LINUX)
		#include <signal.h>
		#define SE_DEBUGBREAK raise(SIGTRAP)

	#else
		#error "Debugbreack not supported"
	#endif

#else

	#define SE_DEBUGBREAK throw std::runtime_error("Assertion failed");

#endif

#define SE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }