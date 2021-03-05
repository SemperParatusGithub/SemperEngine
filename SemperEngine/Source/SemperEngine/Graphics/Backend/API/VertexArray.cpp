#include "Precompiled.h"
#include "VertexArray.h"

#include "Backend.h"
#include "SemperEngine/Graphics/Backend/OpenGL/GLVertexArray.h"

namespace SemperEngine
{
	SharedPtr<VertexArray> VertexArray::Create()
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
			return MakeShared<GLVertexArray>();

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}

		SE_ASSERT_MSG(false, "Unknown Render API");
		return nullptr;
	}

	SharedPtr<VertexArray> VertexArray::Create(VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer)
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
			return MakeShared<GLVertexArray>(vertexBuffer, indexBuffer);

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}

		SE_ASSERT_MSG(false, "Unknown Render API");
		return nullptr;
	}
}