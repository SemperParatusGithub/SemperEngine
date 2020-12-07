#pragma once
#include "SemperEngine/Renderer/IndexBuffer.h"

namespace SemperEngine
{
	class GLIndexBuffer : public IndexBuffer
	{
	public:
		GLIndexBuffer();
		GLIndexBuffer(void *indices, IndexFormat format, uint32_t size);

		virtual ~GLIndexBuffer() override;

		virtual void AddData(void *indices, IndexFormat format, uint32_t size) override;

		virtual inline IndexFormat GetFormat() const noexcept override { return m_Format; }
		virtual inline uint32_t GetCount() const noexcept override { return m_Count; }

		virtual void Bind() const noexcept override;
		virtual void UnBind() const noexcept override;

	public:
		static uint32_t GetSizeOfFormat(IndexFormat format);
		static uint32_t GetGLTypeOfFormat(IndexFormat format);

	private:
		RendererID m_RendererID;
		uint32_t m_Count;
		IndexFormat m_Format;
	};
}