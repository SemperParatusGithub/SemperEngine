#include "Precompiled.h"
#include "Texture.h"

#include "Backend.h"
#include "SemperEngine/Graphics/Backend/OpenGL/GLTexture.h"


namespace SemperEngine
{
	SharedPtr<Texture2D> Texture2D::Create(TextureInfo info)
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
			return MakeShared<GLTexture2D>(info);

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}
	}
	SharedPtr<Texture2D> Texture2D::Create(ConstRef<std::string> filepath, TextureInfo info)
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
			return MakeShared<GLTexture2D>(filepath, info);

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}
	}
	SharedPtr<Texture2D> Texture2D::Create(U32 width, U32 height, TextureInfo info)
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
			return MakeShared<GLTexture2D>(width, height, info);

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}
	}
}