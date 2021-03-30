#pragma once

#include "SemperEngine/Core/Types.h"
#include "SemperEngine/Graphics/Backend/API/Texture.h"
#include "SemperEngine/Graphics/Backend/API/Shader.h"


namespace SemperEngine
{
	enum class MaterialFlag
	{
		None   = 1 << 0,
		NoFill = 1 << 1
	};

	struct PBRMaterialParameters
	{
		Vec3 albedoColor = Vec3(0.0f, 0.0f, 0.0f);
		float metalness = 0.0f;
		float roughness = 0.0f;
	};
	struct PBRMaterialTextures
	{
		bool useAlbedoTexture = false;
		bool useNormalMapTexture = false;
		bool useRoughnessTexture = false;
		bool useMetalnessTexture = false;

		SharedPtr<Texture2D> albedoTexture;
		SharedPtr<Texture2D> normalMapTexture;
		SharedPtr<Texture2D> metalnessTexture;
		SharedPtr<Texture2D> roughnessTexture;
	};

	class Renderer;
	class SubMaterial;

	class Material
	{
	public:
		Material(ConstRef<std::string> name);
		Material(ConstRef<std::string> name, const std::vector<SubMaterial> subMaterials);
		~Material() = default;

		std::string GetName() const;

		void SetFlag(MaterialFlag flag, bool value = true);
		bool GetFlag(MaterialFlag flag);

		void AddSubMaterial(ConstRef<SubMaterial> material);

		std::vector<SubMaterial> &GetSubMaterials();

	private:
		std::string m_MaterialName;

		std::vector<SubMaterial> m_SubMaterials;
		SharedPtr<Shader> m_MaterialShader;
		U32 m_MaterialFlags;

		friend class Renderer;
		friend class Inspector;
	};

	class SubMaterial
	{
	public:
		SubMaterial(ConstRef<std::string> name);
		~SubMaterial() = default;

		std::string GetName() const;

		ConstRef<PBRMaterialParameters> GetPBRMaterialParameters() const;
		PBRMaterialParameters &GetPBRMaterialParameters();

		ConstRef<PBRMaterialTextures> GetPBRMaterialTextures() const;
		PBRMaterialTextures &GetPBRMaterialTextures();	

	private:
		std::string m_SubMaterialName;

		PBRMaterialParameters m_Parameters;
		PBRMaterialTextures m_Textures;
	};
}