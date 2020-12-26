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
		static VertexBuffer *Create(const void *vertices, U32 size, BufferUsage usage);

		virtual void SetData(const void *vertices, U32 size) = 0;

		virtual void AddAttribute(const VertexAttribute &element) = 0;
		virtual const std::vector<VertexAttribute> &GetElements() const = 0;

		virtual U32 GetStride() const = 0;

		virtual void Bind() const noexcept = 0;
		virtual void UnBind() const noexcept = 0;

		friend class VertexAttribute;
	};
}