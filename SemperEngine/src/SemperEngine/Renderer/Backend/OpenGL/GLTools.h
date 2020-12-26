#pragma once
#include "SemperEngine/Core/Types.h"


namespace SemperEngine
{
	using RendererID = U32;

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
		static U32 IndexFormatSize(IndexFormat format);
		static U32 IndexFormatToGLType(IndexFormat format);

		static U32 BufferUsageGLUsage(BufferUsage usage);

		static U32 TextureWrapToGL(TextureWrap wrap);
		static U32 TextureFormatToGL(TextureFormat format);
		static U32 TextureFormatToInternalFormat(U32 format);
		static TextureFormat BitsToTextureFormat(U32 bits);
	};
}