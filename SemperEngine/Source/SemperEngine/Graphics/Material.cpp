#include "Precompiled.h"
#include "Material.h"

#include "SemperEngine/Graphics/Renderers/Renderer.h"


namespace SemperEngine
{
	Material::Material(ConstRef<std::string> name):
		m_MaterialName(name),
		m_MaterialFlags(0)
	{
		m_MaterialShader = Renderer::GetShaderManager()->GetShader("PBR");
	}
	Material::Material(ConstRef<std::string> name, const std::vector<SubMaterial> subMaterials) :
		m_MaterialName(name),
		m_SubMaterials(subMaterials),
		m_MaterialFlags(0)
	{
		m_MaterialShader = Renderer::GetShaderManager()->GetShader("PBR");
	}

	void Material::OnImGui()
	{
		if (ImGui::CollapsingHeader("Materials"))
		{
			for (auto &subMaterial : m_SubMaterials)
				ImGui::Text("%s", subMaterial.GetName().c_str());
		}
	}

	std::string Material::GetName() const
	{
		return m_MaterialName;
	}
	void Material::SetFlag(MaterialFlag flag, bool value)
	{
		if (value)
			m_MaterialFlags |= (U32) flag;
		else
			m_MaterialFlags &= ~(U32) flag;

	}
	bool Material::GetFlag(MaterialFlag flag)
	{
		return (U32) flag & m_MaterialFlags;
	}

	void Material::AddSubMaterial(ConstRef<SubMaterial> material)
	{
		m_SubMaterials.push_back(material);
	}

	ConstRef<std::vector<SubMaterial>> Material::GetSubMaterials() const
	{
		return m_SubMaterials;
	}


	SubMaterial::SubMaterial(ConstRef<std::string> name) : 
		m_SubMaterialName(name)
	{
	}

	std::string SubMaterial::GetName() const
	{
		return m_SubMaterialName;
	}

	ConstRef<PBRMaterialParameters> SubMaterial::GetPBRMaterialParameters() const
	{
		return m_Parameters;
	}
	PBRMaterialParameters &SubMaterial::GetPBRMaterialParameters()
	{
		return m_Parameters;
	}

	ConstRef<PBRMaterialTextures> SubMaterial::GetPBRMaterialTextures() const
	{
		return m_Textures;
	}
	PBRMaterialTextures &SubMaterial::GetPBRMaterialTextures()
	{
		return m_Textures;
	}
}