#include "Precompiled.h"
#include "Material.h"

#include "SemperEngine/Graphics/Renderers/Renderer.h"


namespace SemperEngine
{
	Material::Material(ConstRef<std::string> materialName, SharedPtr<Shader> shader) :
		m_MaterialName(materialName),
		m_Shader(shader)
	{
	}

	void Material::SetName(ConstRef<std::string> materialName)
	{
		m_MaterialName = materialName;
	}
	void Material::SetShader(SharedPtr<Shader> shader)
	{
		m_Shader = shader;
	}

	ConstRef<std::string> Material::GetName() const
	{
		return m_MaterialName;
	}
	ConstRef<SharedPtr<Shader>> Material::GetShader() const
	{
		return m_Shader;
	}

	ConstRef<PBRMaterialParameters> Material::GetPBRMaterialParameters() const
	{
		return m_Parameters;
	}
	PBRMaterialParameters &Material::GetPBRMaterialParameters()
	{
		return m_Parameters;
	}

	ConstRef<PBRMaterialTextures> Material::GetPBRMaterialTextures() const
	{
		return m_Textures;
	}
	PBRMaterialTextures &Material::GetPBRMaterialTextures()
	{
		return m_Textures;
	}
}