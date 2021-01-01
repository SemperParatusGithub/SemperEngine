#pragma once
#include "SemperEngine/Graphics/Backend/API/Framebuffer.h"


namespace SemperEngine
{
	class GLFramebuffer : public Framebuffer
	{
	public:
		GLFramebuffer(ConstRef<FramebufferInfo> info);
		virtual ~GLFramebuffer() override;

		virtual void Bind() const noexcept override;
		virtual void UnBind() const noexcept override;

		virtual void OnResize(U32 width, U32 height) override;
		virtual void *GetColorAttachmentHandle() const noexcept override;

		void Invalidate();

	private:
		FramebufferInfo m_Info;
		RendererID m_RendererID;
		U32 m_ColorAttachment, m_DepthAttachment;
	};
}