#pragma once
#include "SemperEngine/Core/Types.h"

#include"Backend/API/Texture.h"
#include "Transform.h"


namespace SemperEngine
{
	class Renderable2D
	{
	public:
		Renderable2D() = default;
		virtual ~Renderable2D() = default;

		ConstRef<Vec2> GetPosition() const noexcept;
		ConstRef<Vec2> GetScale() const noexcept;
		float GetRotation() const noexcept;

		ConstRef<Transform> GetTransform() const noexcept;

		ConstRef<Vec4> GetColor() const noexcept;
		Texture2D *GetTexture() const noexcept;	// Returns nullptr if no texture is set

		ConstRef<std::array<Vec2, 4>> GetTextureCoordinates() const noexcept;

	protected:
		Transform m_Transform;
		std::array<Vec2, 4> m_TextureCoordinates;

		Vec4 m_Color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
		Texture2D *m_Texture = nullptr;
	};
}