#pragma once
#include "SemperEngine/Graphics/Backend/API/Texture.h"
#include "GLTools.h"


namespace SemperEngine
{
	class GLTexture2D : public Texture2D
	{
	public:
		GLTexture2D(TextureData data = TextureData(), TextureLoadOptions loadOptions = TextureLoadOptions());
		GLTexture2D(const std::string &filepath, TextureData data = TextureData(), TextureLoadOptions loadOptions = TextureLoadOptions());
		GLTexture2D(U32 width, U32 height, TextureData data = TextureData(), TextureLoadOptions loadOptions = TextureLoadOptions());

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

		TextureData m_TextureData;
		TextureLoadOptions m_TextureLoadOptions;
	};
}