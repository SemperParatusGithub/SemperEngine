#include "Precompiled.h"
#include "Sprite.h"


namespace SemperEngine
{
	Sprite::Sprite()
	{
		m_TextureCoordinates[0] = { 0.0f, 0.0f };
		m_TextureCoordinates[1] = { 1.0f, 0.0f };
		m_TextureCoordinates[2] = { 1.0f, 1.0f };
		m_TextureCoordinates[3] = { 0.0f, 1.0f };
	}

	Sprite::Sprite(SharedPtr<Texture2D> texture)
	{
		m_Texture = texture;

		m_TextureCoordinates[0] = { 0.0f, 0.0f };
		m_TextureCoordinates[1] = { 1.0f, 0.0f };
		m_TextureCoordinates[2] = { 1.0f, 1.0f };
		m_TextureCoordinates[3] = { 0.0f, 1.0f };
	}
	Sprite::Sprite(SharedPtr<Texture2D> texture, ConstRef<Vec2> index, ConstRef<Vec2> cellSize)
	{
		m_Texture = texture;

		Vec2 spriteSize = { texture->GetWidth(), texture->GetHeight() };

		Vec2 min = { (index.x * cellSize.x) / texture->GetWidth(), (index.y * cellSize.y) / texture->GetHeight() };
		Vec2 max = { ((index.x + spriteSize.x) * cellSize.x) / texture->GetWidth(), ((index.y + spriteSize.y) * cellSize.y) / texture->GetHeight() };

		m_TextureCoordinates[0] = { min.x, min.y };
		m_TextureCoordinates[1] = { max.x, min.y };
		m_TextureCoordinates[2] = { max.x, max.y };
		m_TextureCoordinates[3] = { min.x, max.y };
	}

	Sprite::Sprite(ConstRef<Vec4> color)
	{
		m_Color = color;

		m_TextureCoordinates[0] = { 0.0f, 0.0f };
		m_TextureCoordinates[1] = { 1.0f, 0.0f };
		m_TextureCoordinates[2] = { 1.0f, 1.0f };
		m_TextureCoordinates[3] = { 0.0f, 1.0f };
	}

	ConstRef<Vec4> Sprite::GetColor() const
	{
		return m_Color;
	}

	SharedPtr<Texture2D> Sprite::GetTexture() const
	{
		return m_Texture;
	}

	ConstRef<std::array<Vec2, 4>> Sprite::GetTextureCoordinates() const
	{
		return m_TextureCoordinates;
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::SetTexture(SharedPtr<Texture2D> texture)
	{
		m_Texture = texture;
	}
	void Sprite::SetSpriteSheet(SharedPtr<Texture2D> texture, ConstRef<Vec2> index, ConstRef<Vec2> cellSize)
	{
		m_Texture = texture;

		Vec2 spriteSize = { texture->GetWidth(), texture->GetHeight() };

		Vec2 min = { (index.x * cellSize.x) / texture->GetWidth() , (index.y * cellSize.y) / texture->GetHeight() };
		Vec2 max = { ((index.x + spriteSize.x) * cellSize.x) / texture->GetWidth() , ((index.y + spriteSize.y) * cellSize.y) / texture->GetHeight() };

		m_TextureCoordinates[0] = { min.x, min.y };
		m_TextureCoordinates[1] = { max.x, min.y };
		m_TextureCoordinates[2] = { max.x, max.y };
		m_TextureCoordinates[3] = { min.x, max.y };
	}

	void Sprite::SetColor(ConstRef<Vec4> color)
	{
		m_Color = color;
	}
}