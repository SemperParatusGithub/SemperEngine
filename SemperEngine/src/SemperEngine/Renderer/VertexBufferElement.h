#pragma once
#include <iostream>

namespace SemperEngine
{
	enum class VertexFormat;

	class VertexAttribute
	{
	public:
		std::string name;
		VertexFormat format;
		bool normalized = false;

		mutable uint32_t offset;

		uint32_t GetSize() const noexcept;
		uint32_t GetComponentCount() const noexcept;
		uint32_t GetComponentOpenGLDataType() const noexcept;
	};
}