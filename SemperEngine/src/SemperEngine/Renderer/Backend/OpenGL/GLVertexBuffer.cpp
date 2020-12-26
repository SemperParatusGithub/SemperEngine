#include "pch.h"
#include "GLVertexBuffer.h"

#include <glad/glad.h>

namespace SemperEngine
{
	GLVertexBuffer::GLVertexBuffer(BufferUsage usage) : 
		m_Stride(0)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GLTools::BufferUsageGLUsage(usage));
	}

	GLVertexBuffer::GLVertexBuffer(const void *vertices, U32 size, BufferUsage usage) :
		m_Stride(0)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GLTools::BufferUsageGLUsage(usage));
	}

	GLVertexBuffer::~GLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void GLVertexBuffer::SetData(const void *vertices, U32 size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
	}

	void GLVertexBuffer::AddAttribute(const VertexAttribute &element)
	{
		m_Stride += element.GetSize();
		element.offset = 0;

		for (std::size_t i = 0; i < m_VertexBufferElements.size(); i++)
		{
			element.offset += m_VertexBufferElements[i].GetSize();
		}
		m_VertexBufferElements.push_back(element);
	}

	const std::vector<VertexAttribute> &GLVertexBuffer::GetElements() const
	{
		return m_VertexBufferElements;
	}

	U32 GLVertexBuffer::GetStride() const
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
