#include "pch.h"
#include "VertexBufferElement.h"
#include "VertexBuffer.h"

#include <glad/glad.h>
#include "SemperEngine/Core/Assert.h"


namespace SemperEngine
{
	u32 VertexAttribute::GetSize() const noexcept
	{
		switch (format)
		{
			case VertexFormat::Float1: return 1 * sizeof(float); break;
			case VertexFormat::Float2: return 2 * sizeof(float); break;
			case VertexFormat::Float3: return 3 * sizeof(float); break;
			case VertexFormat::Float4: return 4 * sizeof(float); break;

			default:
				SE_ASSERT_MSG(false, "Unknown VertexFormat");
				return 0;
				break;
		}
	}

	u32 VertexAttribute::GetComponentCount() const noexcept
	{
		switch (format)
		{
			case VertexFormat::Float1: return 1; break;
			case VertexFormat::Float2: return 2; break;
			case VertexFormat::Float3: return 3; break;
			case VertexFormat::Float4: return 4; break;

			default:
				SE_ASSERT_MSG(false, "Unknown VertexFormat");
				return 0;
				break;
		}
	}

	u32 VertexAttribute::GetComponentOpenGLDataType() const noexcept
	{
		switch (format)
		{
			case VertexFormat::Float1: return GL_FLOAT; break;
			case VertexFormat::Float2: return GL_FLOAT; break;
			case VertexFormat::Float3: return GL_FLOAT; break;
			case VertexFormat::Float4: return GL_FLOAT; break;

			default:
				SE_ASSERT_MSG(false, "Unknown VertexFormat");
				return 0;
				break;
		}
	}
}