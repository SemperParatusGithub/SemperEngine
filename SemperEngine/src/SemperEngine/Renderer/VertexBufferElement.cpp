#include "pch.h"
#include "VertexBufferElement.h"
#include <glad/glad.h>
#include "SemperEngine/Core/Assert.h"


namespace SemperEngine
{
	uint32_t VertexBufferElement::GetSize() const noexcept
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

	uint32_t VertexBufferElement::GetComponentCount() const noexcept
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

	uint32_t VertexBufferElement::GetComponentOpenGLDataType() const noexcept
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