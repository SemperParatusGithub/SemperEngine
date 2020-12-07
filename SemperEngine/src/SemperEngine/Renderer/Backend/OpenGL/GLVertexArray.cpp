#include "pch.h"
#include "GLVertexArray.h"

#include <glad/glad.h>

namespace SemperEngine
{
	GLVertexArray::GLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}
	GLVertexArray::GLVertexArray(VertexBuffer *vertexBuffer, IndexBuffer *indexBuffer)
	{
		glCreateVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);

		m_VertexBuffers.push_back(vertexBuffer);
		m_IndexBuffer = indexBuffer;

		vertexBuffer->Bind();
		indexBuffer->Bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	}
	GLVertexArray::~GLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	VertexArray *GLVertexArray::AddVertexBuffer(VertexBuffer *vertexBuffer)
	{
		m_VertexBuffers.push_back(vertexBuffer);

		// Bind the Vertex Array and the Index Buffer an it magically links together (OpenGL Stuff)
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

		return this;
	}
	VertexArray *GLVertexArray::AddIndexBuffer(IndexBuffer *indexBuffer)
	{
		m_IndexBuffer = indexBuffer;

		// Bind the Vertex Array and the Index Buffer an it magically links together (OpenGL Stuff)
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		return this;
	}
	void GLVertexArray::Bind() const noexcept
	{
		glBindVertexArray(m_RendererID);
	}
	void GLVertexArray::UnBind() const noexcept
	{
		glBindVertexArray(0);
	}
	const std::vector<VertexBuffer *> &GLVertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}
	const IndexBuffer *GLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}
}