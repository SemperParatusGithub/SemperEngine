#include "Precompiled.h"
#include "Texture.h"

#include "Backend.h"
#include "SemperEngine/Graphics/Backend/OpenGL/GLTexture.h"


namespace SemperEngine
{
	Texture2D *Texture2D::Create(TextureData data, TextureLoadOptions loadOptions)
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
			return new GLTexture2D(data, loadOptions);

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}
	}
	Texture2D *Texture2D::Create(const std::string &filepath, TextureData data, TextureLoadOptions loadOptions)
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
			return new GLTexture2D(filepath, data, loadOptions);

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}
	}
	Texture2D *Texture2D::Create(U32 width, U32 height, TextureData data, TextureLoadOptions loadOptions)
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
			return new GLTexture2D(width, height, data, loadOptions);

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}
	}
}