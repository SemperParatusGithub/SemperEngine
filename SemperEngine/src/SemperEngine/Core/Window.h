#pragma once

#include <iostream>
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

        virtual inline uint32_t GetWidth() const = 0;
        virtual inline uint32_t GetHeight() const = 0;

        virtual void *GetNativeWindow() = 0;

        virtual void SetInterval(int interval) = 0;

        static Window *Create(uint32_t width = 1280, uint32_t height = 720, const std::string &title = "Semper Engine");
    };

}