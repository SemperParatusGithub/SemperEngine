#pragma once
#include "SemperEngine/Renderer/VertexBuffer.h"
#include <vector>

namespace SemperEngine
{
	class GLVertexBuffer : public VertexBuffer
	{
	public:
		GLVertexBuffer();
		GLVertexBuffer(void *vertices, uint32_t size);

		~GLVertexBuffer() override;

		virtual void AddElement(VertexBufferElement &&element) override;

		virtual void Bind() const noexcept override;
		virtual void UnBind() const noexcept override;

	private:
		RendererID m_RendererID;
		std::vector<VertexBufferElement> m_VertexBufferElements;
	};
}