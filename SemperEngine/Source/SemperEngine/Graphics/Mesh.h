#pragma once

#include "SemperEngine/Core/Types.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>

#include "SemperEngine/Graphics/Backend/API/VertexArray.h"
#include "SemperEngine/Graphics/Backend/API/Shader.h"
#include "SemperEngine/Graphics/Material.h"


namespace SemperEngine
{
	class Renderer;
	struct MeshComponent;

	struct Vertex
	{
		Vec3 position;
		Vec3 normal;
		Vec3 tangent;
		Vec3 bitangent;
		Vec2 texCoords;
	};

	class SubMesh
	{
	public:
		SubMesh(const std::vector<Vertex> &vertices, const std::vector<U32> &indices, SharedPtr<Material> material);
		~SubMesh();

		inline ConstRef<SharedPtr<Material>> GetMaterial() const { return m_Material; }

	private:
		void PreparePipeline();

	private:
		std::vector<Vertex> m_Vertices;
		std::vector<U32> m_Indices;

		SharedPtr<Material> m_Material;

		SharedPtr<VertexArray> m_VertexArray;
		SharedPtr<VertexBuffer> m_VertexBuffer;
		SharedPtr<IndexBuffer> m_IndexBuffer;

		friend class Renderer;
		friend class Inspector;
	};

	class Mesh
	{
	public:
		Mesh();
		Mesh(ConstRef<std::string> filepath);
		~Mesh();

		void Load(ConstRef<std::string> filepath);

		auto begin() const noexcept { return m_SubMeshes.begin(); }
		auto end() const noexcept { return m_SubMeshes.end(); }

	private:
		void ProcessNode(aiNode *node);
		SubMesh ProcessMesh(aiMesh *mesh);

	private:
		std::string m_Filepath;
		bool m_IsLoaded;
		std::vector<SubMesh> m_SubMeshes;

		const aiScene *m_Scene;

		// Metrics
		U32 m_NumVertices = 0, m_NumIndices = 0;
		U32 m_NumSubMeshes = 0;

		friend class Renderer;
		friend class MeshComponent;
		friend class Inspector;
	};
}