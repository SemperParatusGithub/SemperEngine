#include "pch.h"
#include "GLVertexBuffer.h"

#include <glad/glad.h>

namespace SemperEngine
{
	GLVertexBuffer::GLVertexBuffer() : 
		m_Stride(0)
	{
		glCreateBuffers(1, &m_RendererID);
	}

	GLVertexBuffer::GLVertexBuffer(void *vertices, uint32_t size) : 
		m_Stride(0)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	GLVertexBuffer::~GLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void GLVertexBuffer::AddElement(VertexBufferElement element)
	{
		m_Stride += element.GetSize();
		element.offset = 0;

		for (std::size_t i = 0; i < m_VertexBufferElements.size(); i++)
		{
			element.offset += m_VertexBufferElements[i].GetSize();
		}
		m_VertexBufferElements.emplace_back(element);
	}

	const std::vector<VertexBufferElement> &GLVertexBuffer::GetElements() const
	{
		return m_VertexBufferElements;
	}

	uint32_t GLVertexBuffer::GetStride() const
	{
		return m_Stride;
	}

	void GLVertexBuffer::Bind() const noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void GLVertexBuffer::UnBind() const noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
