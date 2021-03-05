#include "Precompiled.h"
#include "Framebuffer.h"

#include "SemperEngine/Graphics/Backend/API/Backend.h"
#include "SemperEngine/Graphics/Backend/OpenGL/GLFramebuffer.h"


namespace SemperEngine
{
    SharedPtr<Framebuffer> Framebuffer::Create(ConstRef<FramebufferInfo> info)
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
			return MakeShared<GLFramebuffer>(info);

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}

		SE_ASSERT_MSG(false, "Unknown Render API");
		return nullptr;
    }
}