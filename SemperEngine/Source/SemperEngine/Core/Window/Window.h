#pragma once

#include "SemperEngine/Core/Types.h"
#include "SemperEngine/Core/Defines.h"
#include "SemperEngine/Events/Event.h"


namespace SemperEngine
{
    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void SetEventCallbackFunction(const std::function<void(Event &)> &callbackFunction) = 0;

        virtual void OnUpdate() = 0;

        virtual inline U32 GetWidth() const = 0;
        virtual inline U32 GetHeight() const = 0;

        virtual void *GetNativeWindow() = 0;

        virtual void SetMinimumSize(U32 width, U32 height) = 0;
        virtual void SetInterval(I32 interval) = 0;

        static Window *Create(U32 width = 1280, U32 height = 720, const std::string &title = "Semper Engine");
    };
}