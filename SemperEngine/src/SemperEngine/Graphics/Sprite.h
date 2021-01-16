#pragma once
#include "Renderable2D.h"


namespace SemperEngine
{
	class Sprite : public Renderable2D
	{
	public:
		Sprite(SharedPtr<Texture2D> texture);
		Sprite(SharedPtr<Texture2D>, ConstRef<Vec2> index, ConstRef<Vec2> cellSize, ConstRef<Vec2> spriteSize);

		Sprite(ConstRef<Vec4> color);

		virtual ~Sprite() override;

		void SetPosition(ConstRef<Vec2> position);
		void SetScale(ConstRef<Vec2> scale);
		void SetRotation(float rotation);	

		void SetTexture(SharedPtr<Texture2D> texture);
		void SetSpriteSheet(SharedPtr<Texture2D> texture, ConstRef<Vec2> index, ConstRef<Vec2> cellSize, ConstRef<Vec2> spriteSize);
		void SetColor(ConstRef<Vec4> color);
	};
}