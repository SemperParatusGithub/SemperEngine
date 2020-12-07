#include "pch.h"
#include "Window.h"
#include "Platforms.h"

#if defined(SE_PLATFORM_WINDOWS)
    #include "Platform/GLFW/WindowGLFW.h"
#endif

namespace SemperEngine
{

    Window *Window::Create(uint32_t width, uint32_t height, const std::string &title)
    {
        #if defined(SE_PLATFORM_WINDOWS)
            return new WindowGLFW(width, height, title);

        #elif defined(SE_PLATFORM_LINUX)
            #error ""
            return nullptr;

        #elif defined(SE_PLATFORM_IOS)
            #error "" 
            return nullptr;

        #elif defined(SE_PLATFORM_MACOS)
            #error ""
            return nullptr;

        #elif defined(SE_PLATFORM_ANDROID)
            #error ""
            return nullptr;

        #else
            #error "Unknown Platform!"
            return nullptr;

        #endif
    }

}