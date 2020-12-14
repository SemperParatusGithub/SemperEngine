#include "pch.h"
#include "GLTexture.h"

#include "SemperEngine/Core/Assert.h"

#include <glad/glad.h>
#include <stb_image.h>


namespace SemperEngine
{
	GLTexture2D::GLTexture2D(TextureData data, TextureLoadOptions loadOptions) :
		m_Filepath(""),
		m_Width(0), m_Height(0),
		m_TextureData(data),
		m_TextureLoadOptions(loadOptions)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	}
	GLTexture2D::GLTexture2D(const std::string &filepath, TextureData data, TextureLoadOptions loadOptions) : 
		m_Filepath(filepath),
		m_TextureData(data),
		m_TextureLoadOptions(loadOptions)
	{
		m_RendererID = LoadFromFile();
	}
	GLTexture2D::GLTexture2D(uint32_t width, uint32_t height, TextureData data, TextureLoadOptions loadOptions)
	{
		m_Width = 0;
		m_Height = 0;
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGBA8, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	GLTexture2D::~GLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void *GLTexture2D::GetHandle() const noexcept
	{
		return (void *) m_RendererID;
	}

	uint32_t GLTexture2D::GetWidth() const noexcept
	{
		return m_Width;
	}
	uint32_t GLTexture2D::GetHeight() const noexcept
	{
		return m_Height;
	}

	void GLTexture2D::Bind(uint32_t slot) const noexcept
	{
		glBindTextureUnit(slot, m_RendererID);
	}
	void GLTexture2D::UnBind(uint32_t slot) const noexcept
	{
		glBindTextureUnit(slot, 0);
	}

	RendererID GLTexture2D::LoadFromFile()
	{
		int texWidth, texHeight;
		int sizeofChannel = 8;
		int texChannels = 0;

		if (m_TextureLoadOptions.flipY)
			stbi_set_flip_vertically_on_load(true);

		stbi_uc *localBuffer;
		localBuffer = stbi_load(m_Filepath.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

		SE_ASSERT_MSG(localBuffer, "Failed to load Texture %s", m_Filepath.c_str());

		m_Width = static_cast<uint32_t>(texWidth);
		m_Height = static_cast<uint32_t>(texHeight);

		//TODO support different texChannels
		if (texChannels != 4)
			texChannels = 4;

		int bits = texChannels * sizeofChannel; // texChannels;	  //32 bits for 4 bytes r g b a
		m_TextureData.textureFormat = GLTools::BitsToTextureFormat(static_cast<uint32_t>(bits));

		uint32_t localHandle;
		glCreateTextures(GL_TEXTURE_2D, 1, &localHandle);
		glTextureStorage2D(localHandle, 1, GL_RGBA8, m_Width, m_Height);

		glTextureParameteri(localHandle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(localHandle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(localHandle, GL_TEXTURE_WRAP_S, GLTools::TextureWrapToGL(m_TextureData.textureWrap));
		glTextureParameteri(localHandle, GL_TEXTURE_WRAP_T, GLTools::TextureWrapToGL(m_TextureData.textureWrap));

		glTextureSubImage2D(localHandle, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

		stbi_image_free(localBuffer);

		return localHandle;
	}
}