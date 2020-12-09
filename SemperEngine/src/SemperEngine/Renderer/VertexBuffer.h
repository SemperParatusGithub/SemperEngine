#pragma once
#include "VertexBufferElement.h"
#include "SemperEngine/Core/Assert.h"


namespace SemperEngine
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		static VertexBuffer *Create();
		static VertexBuffer *Create(void *vertices, uint32_t size);

		virtual void AddElement(VertexBufferElement element) = 0;
		virtual const std::vector<VertexBufferElement> &GetElements() const = 0;

		virtual uint32_t GetStride() const = 0;

		virtual void Bind() const noexcept = 0;
		virtual void UnBind() const noexcept = 0;

		friend class VertexBufferElement;
	};
}