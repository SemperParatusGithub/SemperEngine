#pragma once
#include "SemperEngine/Core/Assert.h"
#include "SemperEngine/Core/Types.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"


namespace SemperEngine
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		static VertexArray *Create();
		static VertexArray *Create(VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer);

		virtual const VertexArray *AddIndexBuffer(IndexBuffer *indexBuffer ) = 0;
		virtual const VertexArray *AddVertexBuffer(VertexBuffer *vertexBuffer) = 0;

		virtual const std::vector<VertexBuffer*> &GetVertexBuffers() const = 0;
		virtual const IndexBuffer *GetIndexBuffer() const = 0;

		virtual void Bind() const noexcept = 0;
		virtual void UnBind() const noexcept = 0;
	};
}
