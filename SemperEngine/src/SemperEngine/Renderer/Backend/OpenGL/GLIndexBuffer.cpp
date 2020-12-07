#include "pch.h"
#include "GLIndexBuffer.h"

#include <glad/glad.h>

namespace SemperEngine
{
	GLIndexBuffer::GLIndexBuffer() :
		m_Count(0),
		m_Format(IndexFormat::Uint32)
	{
		glCreateBuffers(1, &m_RendererID);
	}

	GLIndexBuffer::GLIndexBuffer(void *indices, IndexFormat format, uint32_t size)
	{
		m_Format = format;
		m_Count = size / GetSizeOfFormat(format);

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	GLIndexBuffer::~GLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void GLIndexBuffer::AddData(void *indices, IndexFormat format, uint32_t size)
	{
	}

	void GLIndexBuffer::Bind() const noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void GLIndexBuffer::UnBind() const noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	uint32_t GLIndexBuffer::GetSizeOfFormat(IndexFormat format)
	{
		switch (format)
		{
		case IndexFormat::Uint8:	return sizeof(uint8_t);
		case IndexFormat::Uint16:	return sizeof(uint16_t);
		case IndexFormat::Uint32:	return sizeof(uint32_t);

		default: SE_ASSERT_MSG(false, "Unknown Index Format");
		}
		return 0;
	}
	uint32_t GLIndexBuffer::GetGLTypeOfFormat(IndexFormat format)
	{
		switch (format)
		{
		case IndexFormat::Uint8:	return GL_UNSIGNED_BYTE;
		case IndexFormat::Uint16:	return GL_UNSIGNED_SHORT;
		case IndexFormat::Uint32:	return GL_UNSIGNED_INT;

		default: SE_ASSERT_MSG(false, "Unknown Index Format");
		}
		return 0;
	}
}