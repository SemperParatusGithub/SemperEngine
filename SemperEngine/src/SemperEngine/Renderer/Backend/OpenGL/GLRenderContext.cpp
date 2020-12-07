#include "pch.h"
#include "GLRenderContext.h"
#include "SemperEngine/Core/Assert.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace SemperEngine
{
	GLRenderContext::GLRenderContext(GLFWwindow *windowHandle) :
		m_WindowHandle(windowHandle)
	{
		SE_ASSERT_MSG(windowHandle, "Window Handle is null");
	}

	void GLRenderContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		SE_ASSERT_MSG(status, "Failed to initialize Glad");

		SE_CORE_INFO("Initialized Glad");
		SE_CORE_INFO("OpenGL Version: %s", glGetString(GL_VERSION));
	}
	
	void GLRenderContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}