#include "pch.h"
#include "GLTools.h"

#include "GLVertexBuffer.h"
#include "GLIndexBuffer.h"
#include "GLTexture.h"


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
	uint32_t GLTools::TextureFormatToGL(TextureFormat format)
	{
		switch (format)
		{
			case TextureFormat::RGBA:				return GL_RGBA;
			case TextureFormat::RGB:				return GL_SRGB;
			case TextureFormat::R8:				    return GL_R8;
			case TextureFormat::RG8:				return GL_RG8;
			case TextureFormat::RGB8:				return GL_RGB8;
			case TextureFormat::RGBA8:				return GL_SRGB_ALPHA;//GL_RGBA8;
			case TextureFormat::RGB16:              return GL_RGB16F;
			case TextureFormat::RGBA16:             return GL_RGBA16F;
			case TextureFormat::RGB32:              return GL_RGB32F;
			case TextureFormat::RGBA32:             return GL_RGBA32F;

			default: SE_ASSERT_MSG(false, "Unknown Texture format Format");
		}
	}
	uint32_t GLTools::TextureWrapToGL(TextureWrap wrap)
	{
		switch (wrap)
		{
			case TextureWrap::Clamp:			return GL_CLAMP_TO_EDGE;
			case TextureWrap::ClampToBorder:	return GL_CLAMP_TO_BORDER;
			case TextureWrap::ClampToEdge:		return GL_CLAMP_TO_EDGE;
			case TextureWrap::Repeat:			return GL_REPEAT;
			case TextureWrap::MirroredRepeat:	return GL_MIRRORED_REPEAT;

			default: SE_ASSERT_MSG(false, "Unknown Texture Wrap Format");
		}
	}
	uint32_t GLTools::TextureFormatToInternalFormat(uint32_t format)
	{
		switch (format)
		{
			case GL_RGBA:		return GL_RGBA;
			case GL_RGB:		return GL_RGB;
			case GL_R8:			return GL_RED;
			case GL_RG8:		return GL_RG;
			case GL_RGB8:		return GL_RGB;
			case GL_RGBA8:		return GL_RGBA;
			case GL_RGB16:		return GL_RGB;
			case GL_RGBA16:		return GL_RGBA;
			case GL_RGBA16F:	return GL_RGB;
			case GL_RGB32F:		return GL_RGB;
			case GL_RGBA32F:	return GL_RGBA;
			case GL_SRGB:		return GL_RGB;
			case GL_SRGB_ALPHA:	return GL_RGBA;

			default: SE_ASSERT_MSG(false, "Unknown Texture Format");
		}
	}
	TextureFormat GLTools::BitsToTextureFormat(uint32_t bits)
	{
		switch (bits)
		{
			case 8:	 return TextureFormat::R8;
			case 16: return TextureFormat::RG8;
			case 24: return TextureFormat::RGB8;
			case 32: return TextureFormat::RGBA8;
			case 48: return TextureFormat::RGB16;
			case 64: return TextureFormat::RGBA16;

			default: SE_ASSERT_MSG(false, "Unsupported image bit - depth %d", bits)
			return TextureFormat::RGB8;
		}
	}
}