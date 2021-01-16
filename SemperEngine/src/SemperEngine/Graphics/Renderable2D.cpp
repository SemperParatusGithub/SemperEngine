#include "Precompiled.h"
#include "Renderable2D.h"


namespace SemperEngine
{
	ConstRef<Vec2> Renderable2D::GetPosition() const noexcept
	{
		return Vec2 { m_Transform.GetTranslation().x, m_Transform.GetTranslation().y };
	}
	ConstRef<Vec2> Renderable2D::GetScale() const noexcept
	{
		return Vec2 { m_Transform.GetScale().x, m_Transform.GetScale().y };
	}
	float Renderable2D::GetRotation() const noexcept
	{
		return m_Transform.GetRotation().z;
	}

	ConstRef<Transform> Renderable2D::GetTransform() const noexcept
	{
		return m_Transform;
	}

	ConstRef<Vec4> Renderable2D::GetColor() const noexcept
	{
		return m_Color;
	}
	SharedPtr<Texture2D> Renderable2D::GetTexture() const noexcept
	{
		return m_Texture;
	}

	ConstRef<std::array<Vec2, 4>> Renderable2D::GetTextureCoordinates() const noexcept
	{
		return m_TextureCoordinates;
	}
}