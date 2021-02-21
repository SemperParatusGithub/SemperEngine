#pragma once
#include "SemperEngine/Graphics/Backend/API/Texture.h"
#include "GLTools.h"


namespace SemperEngine
{
	class GLTexture2D : public Texture2D
	{
	public:
		GLTexture2D(TextureInfo info);
		GLTexture2D(ConstRef<std::string> filepath, TextureInfo info);
		GLTexture2D(U32 width, U32 height, TextureInfo info);

		~GLTexture2D();

		virtual void *GetHandle() const noexcept override;

		virtual std::string GetFilepath() const noexcept override;

		virtual uint32_t GetWidth() const noexcept override;
		virtual uint32_t GetHeight() const noexcept override;

		virtual void Bind(U32 slot = 0) const noexcept override;
		virtual void UnBind(U32 slot = 0) const noexcept override;

	private:
		RendererID LoadFromFile();

	private:
		RendererID m_RendererID;
		std::string m_Filepath;
		uint32_t m_Width, m_Height;

		TextureInfo m_TextureInfo;
	};
}