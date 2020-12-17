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

		mutable u32 offset;

		u32 GetSize() const noexcept;
		u32 GetComponentCount() const noexcept;
		u32 GetComponentOpenGLDataType() const noexcept;
	};
}