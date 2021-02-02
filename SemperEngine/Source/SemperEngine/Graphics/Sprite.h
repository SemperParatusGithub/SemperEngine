#pragma once
#include "SemperEngine/Core/Types.h"
#include "SemperEngine/Graphics/Backend/API/Texture.h"
#include <array>


namespace SemperEngine
{
	class Sprite
	{
	public:
		Sprite();
		Sprite(SharedPtr<Texture2D> texture);
		Sprite(SharedPtr<Texture2D>, ConstRef<Vec2> index, ConstRef<Vec2> cellSize);

		Sprite(ConstRef<Vec4> color);

		~Sprite();

		ConstRef<Vec4> GetColor() const;
		SharedPtr<Texture2D> GetTexture() const;
		ConstRef<std::array<Vec2, 4>> GetTextureCoordinates() const;

		void SetTexture(SharedPtr<Texture2D> texture);
		void SetSpriteSheet(SharedPtr<Texture2D> texture, ConstRef<Vec2> index, ConstRef<Vec2> cellSize);
		void SetColor(ConstRef<Vec4> color);

	private:
		SharedPtr<Texture2D> m_Texture;
		Vec4 m_Color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
		std::array<Vec2, 4> m_TextureCoordinates;
	};
}