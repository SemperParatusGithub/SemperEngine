#pragma once
#include "RenderCommands.h"
#include "SemperEngine/Core/Assert.h"

namespace SemperEngine
{
	enum class IndexFormat
	{
		Uint8,
		Uint16,
		Uint32
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		static IndexBuffer *Create();
		static IndexBuffer *Create(void *indices, IndexFormat format, uint32_t count);

		virtual void AddData(void *indices, IndexFormat format, uint32_t count) = 0;

		virtual IndexFormat GetFormat() const noexcept = 0;
		virtual uint32_t GetCount() const noexcept = 0;

		virtual void Bind() const noexcept= 0;
		virtual void UnBind() const noexcept = 0;
	};
}