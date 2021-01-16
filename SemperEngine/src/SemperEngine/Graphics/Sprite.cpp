#include "Precompiled.h"
#include "Sprite.h"


namespace SemperEngine
{
	Sprite::Sprite(SharedPtr<Texture2D> texture)
	{
		m_Texture = texture;

		m_TextureCoordinates[0] = { 0.0f, 0.0f };
		m_TextureCoordinates[1] = { 1.0f, 0.0f };
		m_TextureCoordinates[2] = { 1.0f, 1.0f };
		m_TextureCoordinates[3] = { 0.0f, 1.0f };
	}
	Sprite::Sprite(SharedPtr<Texture2D> texture, ConstRef<Vec2> index, ConstRef<Vec2> cellSize, ConstRef<Vec2> spriteSize)
	{
		m_Texture = texture;

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

	Sprite::~Sprite()
	{
	}

	void Sprite::SetPosition(ConstRef<Vec2> position)
	{
		m_Transform.SetTranslation(Vec3 { position.x, position.y, 0.0f });
	}
	void Sprite::SetScale(ConstRef<Vec2> scale)
	{
		m_Transform.SetTranslation(Vec3 { scale.x, scale.y, 0.0f });
	}
	void Sprite::SetRotation(float rotation)
	{
		m_Transform.SetRotation(Vec3 { 0.0f, 0.0f, rotation });
	}

	void Sprite::SetTexture(SharedPtr<Texture2D> texture)
	{
		m_Texture = texture;
	}
	void Sprite::SetSpriteSheet(SharedPtr<Texture2D> texture, ConstRef<Vec2> index, ConstRef<Vec2> cellSize, ConstRef<Vec2> spriteSize)
	{
		m_Texture = texture;

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