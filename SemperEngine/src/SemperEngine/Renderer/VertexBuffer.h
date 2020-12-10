#pragma once
#include "VertexBufferElement.h"
#include "SemperEngine/Core/Assert.h"


namespace SemperEngine
{
	enum class VertexFormat
	{
		Float1,
		Float2,
		Float3,
		Float4
	};

	enum class BufferUsage
	{
		Static,
		Dynamic,
		Stream
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		static VertexBuffer *Create(BufferUsage usage);
		static VertexBuffer *Create(void *vertices, uint32_t size, BufferUsage usage);

		virtual void AddElement(VertexBufferElement element) = 0;
		virtual const std::vector<VertexBufferElement> &GetElements() const = 0;

		virtual uint32_t GetStride() const = 0;

		virtual void Bind() const noexcept = 0;
		virtual void UnBind() const noexcept = 0;

		friend class VertexBufferElement;
	};
}