#pragma once

#include "SemperEngine/Core/Window.h"
#include "SemperEngine/Renderer/RenderContext.h"

struct GLFWwindow;

namespace SemperEngine
{

    class WindowGLFW : public Window
    {
    public:
        WindowGLFW(u32 width, u32 height, const std::string &title);
        ~WindowGLFW();

        virtual void SetEventCallbackFunction(const std::function<void(Event &)> &callbackFunction) override;

        virtual void OnUpdate() override;

        virtual inline u32 GetWidth()  const noexcept override { return m_WindowData.width;  }
        virtual inline u32 GetHeight() const noexcept override { return m_WindowData.height; }

        virtual void *GetNativeWindow() override;
        virtual void SetInterval(int interval) override;

    private:
        void SetGLFWCallbacks();

    private:
        GLFWwindow *m_Window;
        RenderContext *m_RenderContext;

        struct WindowData
        {
            u32 width = 1280, height = 720;
            std::string title = "Semper Engine";
            std::function<void(Event &)> callback;
        };
        WindowData m_WindowData;
    };

}