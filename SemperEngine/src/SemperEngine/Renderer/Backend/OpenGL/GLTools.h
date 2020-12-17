#pragma once
#include "SemperEngine/Core/Types.h"


namespace SemperEngine
{
	using RendererID = u32;

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
		static u32 IndexFormatSize(IndexFormat format);
		static u32 IndexFormatToGLType(IndexFormat format);

		static u32 BufferUsageGLUsage(BufferUsage usage);

		static u32 TextureWrapToGL(TextureWrap wrap);
		static u32 TextureFormatToGL(TextureFormat format);
		static u32 TextureFormatToInternalFormat(u32 format);
		static TextureFormat BitsToTextureFormat(u32 bits);
	};
}