#pragma once
#include "VertexBuffer.h"


namespace SemperEngine
{
	enum class IndexFormat
	{
		Uint8,
		Uint16,
		Uint32
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		static IndexBuffer *Create(BufferUsage usage);
		static IndexBuffer *Create(void *indices, IndexFormat format, U32 size, BufferUsage usage);

		virtual IndexFormat GetFormat() const noexcept = 0;
		virtual U32 GetCount() const noexcept = 0;

		virtual void Bind() const noexcept= 0;
		virtual void UnBind() const noexcept = 0;
	};
}