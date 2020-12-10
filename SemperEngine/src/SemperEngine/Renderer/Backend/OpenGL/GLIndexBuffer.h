#pragma once
#include "SemperEngine/Renderer/IndexBuffer.h"
#include "GLTools.h"


namespace SemperEngine
{
	class GLIndexBuffer : public IndexBuffer
	{
	public:
		GLIndexBuffer(BufferUsage usage);
		GLIndexBuffer(void *indices, IndexFormat format, uint32_t size, BufferUsage usage);

		virtual ~GLIndexBuffer() override;

		virtual void AddData(void *indices, IndexFormat format, uint32_t size) override;

		virtual inline IndexFormat GetFormat() const noexcept override { return m_Format; }
		virtual inline uint32_t GetCount() const noexcept override { return m_Count; }

		virtual void Bind() const noexcept override;
		virtual void UnBind() const noexcept override;

	private:
		RendererID m_RendererID;
		uint32_t m_Count;
		IndexFormat m_Format;
	};
}