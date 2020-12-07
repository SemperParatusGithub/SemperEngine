#pragma once

namespace SemperEngine
{
	class RenderContext
	{
	public:
		virtual ~RenderContext() = default;
		
		/* Initialize the Render Context   */
		virtual void Init() = 0;

		/* Swaps the front and back buffer */
		virtual void SwapBuffers() = 0;

		static RenderContext *Create(void *windowHandle);
	};
}