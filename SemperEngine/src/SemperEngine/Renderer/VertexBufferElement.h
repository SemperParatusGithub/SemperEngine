#pragma once
#include <iostream>

namespace SemperEngine
{
	enum class VertexFormat;

	class VertexBufferElement
	{
	public:
		std::string name;
		VertexFormat format;
		bool normalized = false;

		uint32_t offset;

		uint32_t GetSize() const noexcept;
		uint32_t GetComponentCount() const noexcept;
		uint32_t GetComponentOpenGLDataType() const noexcept;
	};
}