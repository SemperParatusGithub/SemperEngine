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
	class SceneRenderer;
	struct MeshComponent;

	using Index = U32;

	struct Vertex
	{
		Vec3 position;
		Vec3 normal;
		Vec3 tangent;
		Vec3 bitangent;
		Vec2 texCoords;
	};

	struct SubMesh
	{
		U32 vertexOffset, indexOffset;
		U32 vertexCount, indexCount;
		U32 materialIndex;
		Mat4 transform;
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
		void ProcessNode(aiNode *node, ConstRef<Mat4> parenTransform);
		SubMesh ProcessMesh(aiMesh *mesh, ConstRef<Mat4> meshTransform);

		void PreparePipeline();

	private:
		std::string m_Filepath;
		bool m_IsLoaded;
		std::vector<SubMesh> m_SubMeshes;

		SharedPtr<Material> m_Material;

		const aiScene *m_Scene;

		std::vector<Vertex> m_Vertices;
		std::vector<Index> m_Indices;

		// Pipeline
		SharedPtr<VertexArray> m_VertexArray;
		SharedPtr<VertexBuffer> m_VertexBuffer;
		SharedPtr<IndexBuffer> m_IndexBuffer;

		friend class Renderer;
		friend class SceneRenderer;
		friend class MeshComponent;
		friend class Inspector;
	};
}