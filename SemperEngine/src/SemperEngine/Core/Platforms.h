#pragma once
/* Platform Detectiion */

/* Check for Windows x64 */
#ifdef _WIN32

    #ifdef _WIN64
        #define SE_PLATFORM_WINDOWS

    #else 
        #error "Win32 is not supportet!"

	#endif

/* Check for Linux */
#elif defined(__linux__)
    #define SE_PLATFORM_LINUX
    #error "Linux is not supportet"

/* Check for Apple */
#elif defined(__APPLE__) && defined(__MACH__)

	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"

	#elif TARGET_OS_IPHONE == 1
		#define SE_PLATFORM_IOS
		#error "IOS is not supported!"

	#elif TARGET_OS_MAC == 1
		#define SE_PLATFORM_MACOS
		#error "MacOS is not supported!"

	#else
		#error "Unknown Apple platform!"

	#endif

/* Check for Android */
#elif defined(__ANDROID__)
	#define SE_PLATFORM_ANDROID
	#error "Android is not supported!"

#else
    #error "Unknown Platform"

#endif