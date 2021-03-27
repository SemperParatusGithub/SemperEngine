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

	struct TextureInfo
	{
		TextureInfo() :
			format(TextureFormat::RGBA32),
			minFilter(TextureFilter::Linear),
			magFilter(TextureFilter::Linear),
			wrap(TextureWrap::ClampToEdge),
			flipY(true)
		{
		}
		TextureInfo(TextureFormat format, TextureFilter minFilter, TextureFilter magFilter, TextureWrap wrap, bool flipY = true) :
			format(format),
			minFilter(minFilter),
			magFilter(magFilter),
			wrap(wrap),
			flipY(flipY)
		{
		}

		TextureFormat format;
		TextureFilter minFilter;
		TextureFilter magFilter;
		TextureWrap	  wrap;
		bool		  flipY;
	};


	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void *GetHandle() const = 0;

		virtual bool IsLoaded() const = 0;

		virtual U32 GetWidth() const = 0;
		virtual U32 GetHeight() const = 0;

		virtual std::string GetFilepath() const = 0;

		virtual void Bind(U32 slot = 0) const = 0;
		virtual void UnBind(U32 slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static SharedPtr<Texture2D> Create(TextureInfo data = TextureInfo());
		static SharedPtr<Texture2D> Create(ConstRef<std::string> filepath, TextureInfo info = TextureInfo());
		static SharedPtr<Texture2D> Create(U32 width, U32 height, TextureInfo info = TextureInfo());
	};
}