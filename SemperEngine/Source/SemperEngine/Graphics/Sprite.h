#pragma once
#include "SemperEngine/Util/CerealOverloads.h"
#include <array>

#include "SemperEngine/Core/Types.h"
#include "SemperEngine/Graphics/Backend/API/Texture.h"


namespace SemperEngine
{
	class Sprite
	{
	public:
		Sprite();
		Sprite(ConstRef<Vec4> color);
		Sprite(SharedPtr<Texture2D> texture);
		Sprite(SharedPtr<Texture2D>, ConstRef<Vec2> index, ConstRef<Vec2> cellSize);
		~Sprite();

		bool HasTexture() const;
		bool HasSpriteSheet() const;

		void RemoveTexture();
		void RemoveSpriteSheet();

		void SetColor(ConstRef<Vec4> color);
		void SetTexture(SharedPtr<Texture2D> texture);
		void SetSpriteSheet(SharedPtr<Texture2D> texture, ConstRef<Vec2> index, ConstRef<Vec2> cellSize);

		ConstRef<Vec4> GetColor() const;
		SharedPtr<Texture2D> GetTexture() const;
		ConstRef<std::array<Vec2, 4>> GetTextureCoordinates() const;

		void SetCellIndex(ConstRef<Vec2> index);
		void SetCellSize(ConstRef<Vec2> cellSize);

		ConstRef<Vec2> GetCellIndex() const;
		ConstRef<Vec2> GetCellSize() const;

		template<typename Archive>
		void save(Archive &archive) const
		{
			std::string textureFilepath = "";
			if(m_HasTexture || m_HasSpriteSheet)
				textureFilepath = m_Texture->GetFilepath();

			archive( cereal::make_nvp("HasTexture", m_HasTexture),
					 cereal::make_nvp("HasSpriteSheet", m_HasSpriteSheet),
					 cereal::make_nvp("TextureFilepath", textureFilepath),
					 cereal::make_nvp("Color", m_Color),
					 cereal::make_nvp("TextureCoordinates", m_TextureCoordinates),
					 cereal::make_nvp("CellSize", m_CellSize),
					 cereal::make_nvp("CellIndex", m_CellIndex) );
		}
		template<typename Archive>
		void load(Archive &archive)
		{
			std::string textureFilepath;

			archive( cereal::make_nvp("HasTexture", m_HasTexture),
					 cereal::make_nvp("HasSpriteSheet", m_HasSpriteSheet),
					 cereal::make_nvp("TextureFilepath", textureFilepath),
					 cereal::make_nvp("Color", m_Color),
					 cereal::make_nvp("TextureCoordinates", m_TextureCoordinates),
					 cereal::make_nvp("CellSize", m_CellSize),
					 cereal::make_nvp("CellIndex", m_CellIndex) );
			
			// Load Texture
			if (m_HasTexture || m_HasSpriteSheet || !textureFilepath.empty())
			{
				m_Texture = Texture2D::Create(textureFilepath);
			}
		}

	private:
		void RecalculateTetxureCoordinates();

	private:
		bool m_HasTexture, m_HasSpriteSheet;
		SharedPtr<Texture2D> m_Texture;
		Vec4 m_Color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);

		std::array<Vec2, 4> m_TextureCoordinates;
		Vec2 m_CellIndex;
		Vec2 m_CellSize;
	};
}