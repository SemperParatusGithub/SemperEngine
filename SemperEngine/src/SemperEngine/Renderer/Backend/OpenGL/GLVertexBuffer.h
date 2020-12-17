#pragma once
#include "SemperEngine/Renderer/VertexBuffer.h"
#include "GLTools.h"

#include <vector>


namespace SemperEngine
{
	class GLVertexBuffer : public VertexBuffer
	{
	public:
		GLVertexBuffer(BufferUsage usage);
		GLVertexBuffer(const void *vertices, u32 size, BufferUsage usage);

		~GLVertexBuffer() override;

		virtual void SetData(const void *vertices, u32 size);

		virtual void AddAttribute(const VertexAttribute &element) override;
		virtual const std::vector<VertexAttribute> &GetElements() const override;

		virtual u32 GetStride() const override;

		virtual void Bind() const noexcept override;
		virtual void UnBind() const noexcept override;

	private:
		RendererID m_RendererID;
		std::vector<VertexAttribute> m_VertexBufferElements;
		u32 m_Stride;

		friend class VertexAttribute;
	};
}