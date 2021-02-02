#pragma once
#include "SemperEngine/Core/Types.h"


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

	struct TextureLoadOptions
	{
		bool flipX;
		bool flipY;
		bool generateMipMaps;
			
		TextureLoadOptions()
		{
			flipX = false;
			flipY = true;
			generateMipMaps = false;
		}

		TextureLoadOptions(bool flipX, bool flipY, bool genMips = true) :
			flipX(flipX),
			flipY(flipY),
			generateMipMaps(genMips)
		{
		}
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void *GetHandle() const noexcept = 0;

		virtual U32 GetWidth() const noexcept = 0;
		virtual U32 GetHeight() const noexcept = 0;

		virtual void Bind(U32 slot = 0) const noexcept = 0;
		virtual void UnBind(U32 slot = 0) const noexcept = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Texture2D *Create(TextureData data = TextureData(), TextureLoadOptions loadOptions = TextureLoadOptions());
		static Texture2D *Create(const std::string &filepath, TextureData data = TextureData(), TextureLoadOptions loadOptions = TextureLoadOptions());
		static Texture2D *Create(U32 width, U32 height, TextureData data = TextureData(), TextureLoadOptions loadOptions = TextureLoadOptions());
	};
}