#include "Precompiled.h"
#include "Sprite.h"


namespace SemperEngine
{
	Sprite::Sprite()
	{
		m_HasTexture = false;
		m_HasSpriteSheet = false;

		RecalculateTetxureCoordinates();
	}
	Sprite::Sprite(ConstRef<Vec4> color)
	{
		SetColor(color);
	}
	Sprite::Sprite(SharedPtr<Texture2D> texture)
	{
		SetTexture(texture);
	}
	Sprite::Sprite(SharedPtr<Texture2D> texture, ConstRef<Vec2> index, ConstRef<Vec2> cellSize)
	{
		SetSpriteSheet(texture, index, cellSize);
	}
	Sprite::~Sprite()
	{
	}

	bool Sprite::HasTexture() const
	{
		return m_HasTexture;
	}
	bool Sprite::HasSpriteSheet() const
	{
		return m_HasSpriteSheet;
	}

	void Sprite::RemoveTexture()
	{
		m_HasTexture = false;

		RecalculateTetxureCoordinates();
	}
	void Sprite::RemoveSpriteSheet()
	{
		m_HasSpriteSheet = false;

		RecalculateTetxureCoordinates();
	}

	void Sprite::SetColor(ConstRef<Vec4> color)
	{
		m_Color = color;
	}
	void Sprite::SetTexture(SharedPtr<Texture2D> texture)
	{
		m_HasTexture = true;
		m_HasSpriteSheet = false;

		m_Texture = texture;

		RecalculateTetxureCoordinates();
	}
	void Sprite::SetSpriteSheet(SharedPtr<Texture2D> texture, ConstRef<Vec2> index, ConstRef<Vec2> cellSize)
	{
		m_HasTexture = false;
		m_HasSpriteSheet = true;

		m_Texture = texture;
		m_CellIndex = index;
		m_CellSize = cellSize;

		RecalculateTetxureCoordinates();
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

	void Sprite::SetCellIndex(ConstRef<Vec2> index)
	{
		m_CellIndex = index;

		RecalculateTetxureCoordinates();
	}
	void Sprite::SetCellSize(ConstRef<Vec2> cellSize)
	{
		m_CellSize = cellSize;

		RecalculateTetxureCoordinates();
	}

	ConstRef<Vec2> Sprite::GetCellIndex() const
	{
		return m_CellIndex;
	}
	ConstRef<Vec2> Sprite::GetCellSize() const
	{
		return m_CellSize;
	}

	void Sprite::RecalculateTetxureCoordinates()
	{
		if (m_HasSpriteSheet)
		{
			Vec2 spriteSize = { m_Texture->GetWidth(), m_Texture->GetHeight() };

			Vec2 min = { (m_CellIndex.x * m_CellSize.x) / spriteSize.x, (m_CellIndex.y * m_CellSize.y) / spriteSize.y };
			Vec2 max = { (m_CellIndex.x * m_CellSize.x + m_CellSize.x) / spriteSize.x , (m_CellIndex.y * m_CellSize.y + m_CellSize.y) / spriteSize.y };

			m_TextureCoordinates[0] = { min.x, min.y };
			m_TextureCoordinates[1] = { max.x, min.y };
			m_TextureCoordinates[2] = { max.x, max.y };
			m_TextureCoordinates[3] = { min.x, max.y };
		}
		// simple Texture or color only
		else {	
			m_TextureCoordinates[0] = { 0.0f, 0.0f };
			m_TextureCoordinates[1] = { 1.0f, 0.0f };
			m_TextureCoordinates[2] = { 1.0f, 1.0f };
			m_TextureCoordinates[3] = { 0.0f, 1.0f };
		}
	}
}