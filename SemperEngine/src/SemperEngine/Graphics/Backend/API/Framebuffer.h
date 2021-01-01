#pragma once
#include "SemperEngine/Core/Types.h"


namespace SemperEngine
{
	struct FramebufferInfo
	{
		U32 width, height;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		static Framebuffer *Create(ConstRef<FramebufferInfo> info);

		virtual void Bind() const noexcept = 0;
		virtual void UnBind() const noexcept = 0;

		virtual void OnResize(U32 width, U32 height) = 0;

		virtual void *GetColorAttachmentHandle() const noexcept = 0;
	};
}