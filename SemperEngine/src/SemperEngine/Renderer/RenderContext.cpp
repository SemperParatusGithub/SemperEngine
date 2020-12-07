#include "pch.h"
#include "RenderContext.h"

#include "Backend.h"
#include "Backend/OpenGL/GLRenderContext.h"

namespace SemperEngine
{
	RenderContext *RenderContext::Create(void *windowHandle)
	{
		switch (Backend::GetRenderAPI())
		{
		case Backend::API::DirectX:
			SE_ASSERT_MSG(false, "DirectX not supported");
			return nullptr;

		case Backend::API::None:
			SE_ASSERT_MSG(false, "API::None not supported");
			return nullptr;

		case Backend::API::OpenGL:
			return new GLRenderContext((GLFWwindow *) windowHandle);

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}

		SE_ASSERT_MSG(false, "Unknown Render API");
		return nullptr;
	}
}
