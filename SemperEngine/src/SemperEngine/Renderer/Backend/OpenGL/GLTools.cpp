#include "pch.h"
#include "GLTools.h"

#include "GLVertexBuffer.h"
#include "GLIndexBuffer.h"

#include <glad/glad.h>
#include "SemperEngine/Core/Assert.h"


namespace SemperEngine
{
	uint32_t GLTools::IndexFormatSize(IndexFormat format)
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

	uint32_t GLTools::IndexFormatToGLType(IndexFormat format)
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

	uint32_t GLTools::BufferUsageGLUsage(BufferUsage usage)
	{
		switch (usage)
		{
			case BufferUsage::Static:	return GL_STATIC_DRAW;
			case BufferUsage::Dynamic:	return GL_DYNAMIC_DRAW;
			case BufferUsage::Stream:	return GL_STREAM_DRAW;

			default: SE_ASSERT_MSG(false, "Unknown Buffer usage Format");
		}
		return 0;
	}
}