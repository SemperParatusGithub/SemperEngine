#pragma once
#include "SemperEngine/Graphics/Backend/API/RenderContext.h"


struct GLFWwindow;

namespace SemperEngine
{
	class GLRenderContext : public RenderContext
	{
	public:
		GLRenderContext(GLFWwindow *windowHandle);

		virtual void Init() override;

		virtual void SwapBuffers() override;

	private:
		GLFWwindow *m_WindowHandle;
	};
}