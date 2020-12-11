#pragma once
#include <iostream>


namespace SemperEngine
{
	enum class TextureWrap
	{
		None,
		Repeat,
		Clamp,
		MirroredRepeat,
		ClampToEdge,
		ClampToBorder
	};

	enum class TextureFilter
	{
		None,
		Linear,
		Nearest
	};

	enum class TextureFormat
	{
		None,
		R8,
		RG8,
		RGB8,
		RGBA8,
		RGB16,
		RGBA16,
		RGB32,
		RGBA32,
		RGB,
		RGBA,
		Depth,
		Stencil,
		DepthStencil
	};

	enum class TextureType
	{
		Color,
		Depth,
		DepthArray,
		Cube,
		Other
	};

	struct TextureData
	{
		TextureData() :
			textureType(TextureType::Color),
			textureFormat(TextureFormat::RGBA32),
			minFilter(TextureFilter::Linear),
			magFilter(TextureFilter::Linear),
			textureWrap(TextureWrap::ClampToEdge)
		{
		}
		TextureData(TextureType textureType, TextureFormat textureFormat, TextureFilter minFilter, TextureFilter magFilter, TextureWrap textureWrap) :
			textureType(textureType),
			textureFormat(textureFormat),
			minFilter(minFilter),
			magFilter(magFilter),
			textureWrap(textureWrap)
		{
		}

		TextureType textureType;
		TextureFormat textureFormat;
		TextureFilter minFilter;
		TextureFilter magFilter;
		TextureWrap textureWrap;
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void *GetHandle() const noexcept = 0;

		virtual uint32_t GetWidth() const noexcept = 0;
		virtual uint32_t GetHeight() const noexcept = 0;

		virtual void Bind(uint32_t slot = 0) const noexcept = 0;
		virtual void UnBind() const noexcept = 0;
	};

	class Texture2D : public Texture
	{
	public:
		// static Texture *Create();
		// static Texture *Create(const std::string &filepath);
		// static Texture *Create(uint32_t width, uint32_t height);

		virtual void Load(const std::string &filepath) = 0;
	};
}