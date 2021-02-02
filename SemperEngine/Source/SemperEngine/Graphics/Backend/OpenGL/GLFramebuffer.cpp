#include "Precompiled.h"
#include "GLFramebuffer.h"

#include "SemperEngine/Core/Assert.h"
#include <glad/glad.h>


namespace SemperEngine
{
	GLFramebuffer::GLFramebuffer(ConstRef<FramebufferInfo> info) : 
		m_Info(info)
	{
		Invalidate();
	}
	GLFramebuffer::~GLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void GLFramebuffer::Bind() const noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Info.width, m_Info.height);
	}
	void GLFramebuffer::UnBind() const noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	SemperEngine::Vec2i GLFramebuffer::GetSize() const noexcept
	{
		return Vec2i { m_Info.width, m_Info.height };
	}

	void GLFramebuffer::OnResize(U32 width, U32 height)
	{
		m_Info.width = width;
		m_Info.height = height;

		if (width <= 0)
			m_Info.width = 1;
		if (height <= 0)
			m_Info.height = 1;

		if (width >= 8640)
			m_Info.width = 8640;
		if (height >= 8640)
			m_Info.height = 8640;

		Invalidate();
	}

	void *GLFramebuffer::GetColorAttachmentHandle() const noexcept
	{
		return reinterpret_cast<void *>(m_ColorAttachment);
	}

	void GLFramebuffer::Invalidate()
	{
		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
		}

		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Info.width, m_Info.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Info.width, m_Info.height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

		SE_ASSERT_MSG(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}