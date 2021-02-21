#include "Precompiled.h"
#include "GLTexture.h"

#include "SemperEngine/Core/Assert.h"

#include <glad/glad.h>
#include <stb_image.h>


namespace SemperEngine
{
	GLTexture2D::GLTexture2D(TextureInfo info) :
		m_Filepath(""),
		m_Width(0), m_Height(0),
		m_TextureInfo(info)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	}
	GLTexture2D::GLTexture2D(ConstRef<std::string> filepath, TextureInfo info) : 
		m_Filepath(filepath),
		m_TextureInfo(info)
	{
		m_RendererID = LoadFromFile();
	}
	GLTexture2D::GLTexture2D(U32 width, U32 height, TextureInfo info) : 
		m_Width(width),
		m_Height(height),
		m_TextureInfo(info)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGBA8, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, m_TextureInfo.minFilter == TextureFilter::Linear ? GL_LINEAR : GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, m_TextureInfo.magFilter == TextureFilter::Linear ? GL_LINEAR : GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	GLTexture2D::~GLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void *GLTexture2D::GetHandle() const noexcept
	{
		return reinterpret_cast<void *>(m_RendererID);
	}

	std::string GLTexture2D::GetFilepath() const noexcept
	{
		return m_Filepath;
	}

	U32 GLTexture2D::GetWidth() const noexcept
	{
		return m_Width;
	}
	U32 GLTexture2D::GetHeight() const noexcept
	{
		return m_Height;
	}

	void GLTexture2D::Bind(U32 slot) const noexcept
	{
		glBindTextureUnit(slot, m_RendererID);
	}
	void GLTexture2D::UnBind(U32 slot) const noexcept
	{
		glBindTextureUnit(slot, 0);
	}

	RendererID GLTexture2D::LoadFromFile()
	{
		SE_CORE_INFO("Loading Texture: %s", m_Filepath.c_str());

		int texWidth, texHeight;
		int sizeofChannel = 8;
		int texChannels = 0;

		if (m_TextureInfo.flipY)
			stbi_set_flip_vertically_on_load(true);

		stbi_uc *localBuffer;
		localBuffer = stbi_load(m_Filepath.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);

		SE_ASSERT_MSG(localBuffer, "Failed to load Texture");

		m_Width = static_cast<U32>(texWidth);
		m_Height = static_cast<U32>(texHeight);

		//TODO support different texChannels
		if (texChannels != 4)
			texChannels = 4;

		int bits = texChannels * sizeofChannel; // texChannels;	  //32 bits for 4 bytes r g b a
		m_TextureInfo.format = GLTools::BitsToTextureFormat(static_cast<U32>(bits));

		U32 localHandle;
		glCreateTextures(GL_TEXTURE_2D, 1, &localHandle);
		glTextureStorage2D(localHandle, 1, GL_RGBA8, m_Width, m_Height);

		glTextureParameteri(localHandle, GL_TEXTURE_MIN_FILTER, m_TextureInfo.minFilter == TextureFilter::Linear ? GL_LINEAR : GL_NEAREST);
		glTextureParameteri(localHandle, GL_TEXTURE_MAG_FILTER, m_TextureInfo.magFilter == TextureFilter::Linear ? GL_LINEAR : GL_NEAREST);

		glTextureParameteri(localHandle, GL_TEXTURE_WRAP_S, GLTools::TextureWrapToGL(m_TextureInfo.wrap));
		glTextureParameteri(localHandle, GL_TEXTURE_WRAP_T, GLTools::TextureWrapToGL(m_TextureInfo.wrap));

		glTextureSubImage2D(localHandle, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

		stbi_image_free(localBuffer);

		return localHandle;
	}
}