#pragma once
#include "Defines.h"
#include "SemperEngine/Log/Log.h"

#define GetString(x) 

// TEMP
#define SE_ENABLE_ASSERTS

#ifdef SE_ENABLE_ASSERTS

#define SE_ASSERT_MSG(value, message)										\
		if (!(value))														\
		{																	\
			SE_CORE_ERROR(message);											\
			SE_DEBUGBREAK;													\
		}										


	#define SE_ASSERT(value)												\
		if (!(value))														\
		{																	\
			SE_CORE_ERROR("Assertion Failed: File: , Line: ");				\
			SE_DEBUGBREAK;													\
		}

#endif