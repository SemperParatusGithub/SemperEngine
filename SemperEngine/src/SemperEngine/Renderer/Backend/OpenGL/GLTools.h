#pragma once
#include <iostream>


namespace SemperEngine
{
	// Forward Declarations
	class VertexBuffer;
	enum class VertexFormat;

	class GLIndexBuffer;
	enum class IndexFormat;

	enum class BufferUsage;

	// alias for uint32_t
	using RendererID = uint32_t;

	class GLTools
	{
	public:
		static uint32_t IndexFormatSize(IndexFormat format);
		static uint32_t IndexFormatToGLType(IndexFormat format);

		static uint32_t BufferUsageGLUsage(BufferUsage usage);
	};
}