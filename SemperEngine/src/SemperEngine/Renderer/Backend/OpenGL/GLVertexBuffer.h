#pragma once
#include "SemperEngine/Renderer/VertexBuffer.h"
#include "SemperEngine/Renderer/RenderCommands.h"
#include <vector>

namespace SemperEngine
{
	class GLVertexBuffer : public VertexBuffer
	{
	public:
		GLVertexBuffer();
		GLVertexBuffer(void *vertices, uint32_t size);

		~GLVertexBuffer() override;

		virtual void AddElement(VertexBufferElement element) override;
		virtual const std::vector<VertexBufferElement> &GetElements() const override;

		virtual uint32_t GetStride() const override;

		virtual void Bind() const noexcept override;
		virtual void UnBind() const noexcept override;

	private:
		RendererID m_RendererID;
		std::vector<VertexBufferElement> m_VertexBufferElements;
		uint32_t m_Stride;

		friend class VertexBufferElement;
	};
}