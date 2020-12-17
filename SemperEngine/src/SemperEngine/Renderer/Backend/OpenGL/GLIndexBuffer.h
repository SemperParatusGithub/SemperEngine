#pragma once
#include "SemperEngine/Renderer/IndexBuffer.h"
#include "GLTools.h"


namespace SemperEngine
{
	class GLIndexBuffer : public IndexBuffer
	{
	public:
		GLIndexBuffer(BufferUsage usage);
		GLIndexBuffer(void *indices, IndexFormat format, u32 size, BufferUsage usage);

		virtual ~GLIndexBuffer() override;

		virtual inline IndexFormat GetFormat() const noexcept override { return m_Format; }
		virtual inline u32 GetCount() const noexcept override { return m_Count; }

		virtual void Bind() const noexcept override;
		virtual void UnBind() const noexcept override;

	private:
		RendererID m_RendererID;
		u32 m_Count;
		IndexFormat m_Format;
	};
}