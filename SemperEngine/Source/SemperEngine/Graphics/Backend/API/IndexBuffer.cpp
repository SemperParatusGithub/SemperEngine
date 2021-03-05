#include "Precompiled.h"
#include "IndexBuffer.h"

#include "SemperEngine/Core/Assert.h"
#include "Backend.h"

#include "SemperEngine/Graphics/Backend/OpenGL/GLBackend.h"
#include "SemperEngine/Graphics/Backend/OpenGL/GLIndexBuffer.h"


namespace SemperEngine
{
	SharedPtr<IndexBuffer> IndexBuffer::Create(BufferUsage usage)
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
			return MakeShared<GLIndexBuffer>(usage);

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}

		SE_ASSERT_MSG(false, "Unknown Render API");
		return nullptr;
	}

	SharedPtr<IndexBuffer> IndexBuffer::Create(void *indices, IndexFormat format, U32 size, BufferUsage usage)
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
			return MakeShared<GLIndexBuffer>(indices, format, size, usage);

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}

		SE_ASSERT_MSG(false, "Unknown Render API");
		return nullptr;
	}
}