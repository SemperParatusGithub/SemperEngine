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
		SharedPtr<Texture2D> roughnessTexture;
		SharedPtr<Texture2D> metalnessTexture;
	};

	class Material
	{
	public:
		Material(ConstRef<std::string> materialName, SharedPtr<Shader> shaderName);

		void SetName(ConstRef<std::string> materialName);
		void SetShader(SharedPtr<Shader> shader);

		ConstRef<std::string> GetName() const;
		ConstRef<SharedPtr<Shader>> GetShader() const;

		void AddFlag(MaterialFlag flag);
		void RemoveFlag(MaterialFlag flag);
		bool HasFlag(MaterialFlag flag);

		ConstRef<PBRMaterialParameters> GetPBRMaterialParameters() const;
		PBRMaterialParameters &GetPBRMaterialParameters();

		ConstRef<PBRMaterialTextures> GetPBRMaterialTextures() const;
		PBRMaterialTextures &GetPBRMaterialTextures();	

	private:
		std::string m_MaterialName;
		U32 m_Flags;

		SharedPtr<Shader> m_Shader;

		PBRMaterialParameters m_Parameters;
		PBRMaterialTextures m_Textures;
	};
}