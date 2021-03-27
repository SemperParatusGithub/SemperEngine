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

		virtual void *GetHandle() const override;

		virtual bool IsLoaded() const override;

		virtual std::string GetFilepath() const override;

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;

		virtual void Bind(U32 slot = 0) const override;
		virtual void UnBind(U32 slot = 0) const override;

	private:
		RendererID LoadFromFile();

	private:
		RendererID m_RendererID;
		std::string m_Filepath;
		bool m_IsLoaded;

		uint32_t m_Width, m_Height;
		TextureInfo m_TextureInfo;
	};
}