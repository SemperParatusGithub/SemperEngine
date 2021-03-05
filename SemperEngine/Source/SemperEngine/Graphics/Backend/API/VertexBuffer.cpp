#include "Precompiled.h"
#include "VertexBuffer.h"

#include "Backend.h"
#include "SemperEngine/Graphics/Backend/OpenGL/GLVertexBuffer.h"


namespace SemperEngine
{
	SharedPtr<VertexBuffer> VertexBuffer::Create(BufferUsage usage)
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
			return MakeShared<GLVertexBuffer>(usage);

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}

		SE_ASSERT_MSG(false, "Unknown Render API");
		return nullptr;
	}
	SharedPtr<VertexBuffer> VertexBuffer::Create(const void *vertices, U32 size, BufferUsage usage)
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
			return MakeShared<GLVertexBuffer>(vertices, size, usage);

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}

		SE_ASSERT_MSG(false, "Unknown Render API");
		return nullptr;
	}
}