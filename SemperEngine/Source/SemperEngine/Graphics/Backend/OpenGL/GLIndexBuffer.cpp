#include "Precompiled.h"
#include "GLIndexBuffer.h"

#include "GLTools.h"

#include <glad/glad.h>


namespace SemperEngine
{
	GLIndexBuffer::GLIndexBuffer(BufferUsage usage) :
		m_Count(0),
		m_Format(IndexFormat::Uint32)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GLTools::BufferUsageGLUsage(usage));
	}

	GLIndexBuffer::GLIndexBuffer(void *indices, IndexFormat format, U32 size, BufferUsage usage)
	{
		m_Format = format;
		m_Count = size / GLTools::IndexFormatSize(format);

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, indices, GLTools::BufferUsageGLUsage(usage));
	}

	GLIndexBuffer::~GLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void GLIndexBuffer::Bind() const noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void GLIndexBuffer::UnBind() const noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}