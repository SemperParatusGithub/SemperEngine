#include "pch.h"
#include "GLVertexBuffer.h"

#include <glad/glad.h>

namespace SemperEngine
{
	GLVertexBuffer::GLVertexBuffer()
	{
		glCreateBuffers(1, &m_RendererID);
	}
	GLVertexBuffer::GLVertexBuffer(void *vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	GLVertexBuffer::~GLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void GLVertexBuffer::AddElement(VertexBufferElement &&element)
	{
		m_VertexBufferElements.emplace_back(std::move(element));
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
