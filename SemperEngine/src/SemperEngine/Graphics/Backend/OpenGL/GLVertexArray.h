#pragma once
#include "SemperEngine/Graphics/Backend/API/VertexArray.h"
#include "GLTools.h"


namespace SemperEngine
{
	class GLVertexArray : public VertexArray
	{
	public:
		GLVertexArray();
		GLVertexArray(VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer);

		~GLVertexArray() override;
	
		virtual VertexArray *AddVertexBuffer(VertexBuffer *vertexBuffer) override;
		virtual VertexArray *AddIndexBuffer(IndexBuffer *indexBuffer) override;

		virtual const std::vector<VertexBuffer *> &GetVertexBuffers() const override;
		virtual const IndexBuffer *GetIndexBuffer() const override;

		virtual void Bind() const noexcept override;
		virtual void UnBind() const noexcept override;

	private:
		RendererID m_RendererID;
		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer *m_IndexBuffer;
	};
}
