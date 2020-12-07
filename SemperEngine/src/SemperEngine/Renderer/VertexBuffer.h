#pragma once
#include "SemperEngine/Core/Assert.h"

#include "RenderCommands.h"

namespace SemperEngine
{
	enum class VertexFormat
	{
		Float1,
		Float2,
		Float3, 
		Float4
	};

	struct VertexBufferElement
	{
		std::string name;
		VertexFormat format;
		bool normalized = false;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		static VertexBuffer *Create();
		static VertexBuffer *Create(void *vertices, uint32_t size);

		virtual void AddElement(VertexBufferElement &&element) = 0;

		virtual void Bind() const noexcept = 0;
		virtual void UnBind() const noexcept = 0;
	};
}