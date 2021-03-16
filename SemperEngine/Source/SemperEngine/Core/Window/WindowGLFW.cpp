#include "Precompiled.h"
#include "WindowGLFW.h"

#include "SemperEngine/Log/Log.h"
#include "SemperEngine/Core/Assert.h"

#include "SemperEngine/Events/MouseEvent.h"
#include "SemperEngine/Events/keyEvent.h"
#include "SemperEngine/Events/ApplicationEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace SemperEngine
{
	static U32 s_TotalGLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char *description)
	{
		SE_CORE_ERROR("%d: %s", error, description);
	}

	WindowGLFW::WindowGLFW(U32 width, U32 height, const std::string &title)
	{
		m_WindowData.width  = width;
		m_WindowData.height = height;
		m_WindowData.title  = title;

		if (s_TotalGLFWWindowCount == 0)
		{
			int success = glfwInit();
			if (!success)
				throw std::runtime_error("Failed to init GFLW");
			SE_CORE_INFO("Initialized GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
		}
		else {
			SE_ASSERT_MSG(false, "Currently only one window supported!");
		}

		SE_CORE_INFO("Creating Window: %s (%d, %d)", title.c_str(), width, height);
		m_Window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr, nullptr);
		SE_ASSERT_MSG(m_Window, "Failed to create GLFW Window");
		s_TotalGLFWWindowCount += 1;

		m_RenderContext = RenderContext::Create(m_Window);
		m_RenderContext->Init();

		glfwSetWindowUserPointer(m_Window, &m_WindowData);
		SetGLFWCallbacks();
	}

	WindowGLFW::~WindowGLFW()
	{
		glfwDestroyWindow(m_Window);
		s_TotalGLFWWindowCount -= 1;

		if (s_TotalGLFWWindowCount == 0) 
		{
			glfwTerminate();
		}
	}

	void WindowGLFW::SetEventCallbackFunction(const std::function<void(Event &e)> &callbackFunction)
	{
		m_WindowData.callback = callbackFunction;
	}

	void WindowGLFW::OnUpdate()
	{
		m_RenderContext->SwapBuffers();
		glfwPollEvents();
	}

	void *WindowGLFW::GetNativeWindow()
	{
		return m_Window;
	}

	void WindowGLFW::Maximize()
	{
		glfwMaximizeWindow(m_Window);
	}

	void WindowGLFW::SetTitle(ConstRef<std::string> title)
	{
		glfwSetWindowTitle(m_Window, title.c_str());
	}

	void WindowGLFW::SetMinimumSize(U32 width, U32 height)
	{
		glfwSetWindowSizeLimits(m_Window, width, height, GLFW_DONT_CARE, GLFW_DONT_CARE);
	}

	void WindowGLFW::SetInterval(I32 interval)
	{
		glfwSwapInterval(interval);
	}

	void WindowGLFW::SetGLFWCallbacks()
	{
		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height)
			{
				WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.callback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window)
			{
				WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.callback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
			{
				WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.callback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode)
			{
				WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.callback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods)
			{
				WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.callback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset)
			{
				WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float) xOffset, (float) yOffset);
				data.callback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos)
			{
				WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float) xPos, (float) yPos);
				data.callback(event);
			});
	}
}