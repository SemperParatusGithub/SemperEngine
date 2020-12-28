#pragma once
#include "SemperEngine/Core/Types.h"


namespace SemperEngine
{
	enum class VertexFormat;

	class VertexAttribute
	{
	public:
		std::string name;
		VertexFormat format;
		bool normalized = false;

		mutable U32 offset;

		U32 GetSize() const noexcept;
		U32 GetComponentCount() const noexcept;
		U32 GetComponentOpenGLDataType() const noexcept;
	};
}