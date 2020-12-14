#pragma once
#include <iostream>


namespace SemperEngine
{
	using RendererID = uint32_t;

	// Forward Declarations
	class VertexBuffer;
	enum class VertexFormat;

	class GLIndexBuffer;
	enum class IndexFormat;

	enum class TextureWrap;
	enum class TextureFormat;

	enum class BufferUsage;

	class GLTools
	{
	public:
		static uint32_t IndexFormatSize(IndexFormat format);
		static uint32_t IndexFormatToGLType(IndexFormat format);

		static uint32_t BufferUsageGLUsage(BufferUsage usage);

		static uint32_t TextureWrapToGL(TextureWrap wrap);
		static uint32_t TextureFormatToGL(TextureFormat format);
		static uint32_t TextureFormatToInternalFormat(uint32_t format);
		static TextureFormat BitsToTextureFormat(uint32_t bits);
	};
}