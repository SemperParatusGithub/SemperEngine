#pragma once

#include "Types.h"
#include "Defines.h"
#include "SemperEngine/Events/Event.h"

namespace SemperEngine
{

    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void SetEventCallbackFunction(const std::function<void(Event &)> &callbackFunction) = 0;

        virtual void OnUpdate() = 0;

        virtual inline u32 GetWidth() const = 0;
        virtual inline u32 GetHeight() const = 0;

        virtual void *GetNativeWindow() = 0;

        virtual void SetInterval(i32 interval) = 0;

        static Window *Create(u32 width = 1280, u32 height = 720, const std::string &title = "Semper Engine");
    };

}