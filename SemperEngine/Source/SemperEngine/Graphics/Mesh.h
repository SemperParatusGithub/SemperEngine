#pragma once

#include "SemperEngine/Core/Types.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>

#include "SemperEngine/Graphics/Backend/API/VertexArray.h"
#include "SemperEngine/Graphics/Backend/API/Shader.h"


namespace SemperEngine
{
	class Renderer;

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
		SubMesh(const std::vector<Vertex> &vertices, const std::vector<U32> &indices);
		~SubMesh();

	private:
		void PreparePipeline();

	private:
		std::vector<Vertex> m_Vertices;
		std::vector<U32> m_Indices;

		SharedPtr<VertexArray> m_VertexArray;
		SharedPtr<VertexBuffer> m_VertexBuffer;
		SharedPtr<IndexBuffer> m_IndexBuffer;

		SharedPtr<Shader> m_MeshShader;

		friend class Renderer;
	};

	class Mesh
	{
	public:
		Mesh();
		Mesh(ConstRef<std::string> filepath);
		~Mesh();

		void Load(ConstRef<std::string> filepath);

	private:
		void ProcessNode(aiNode *node);
		SubMesh ProcessMesh(aiMesh *mesh);

	private:
		std::string m_Filepath;
		bool m_IsLoaded;
		std::vector<SubMesh> m_SubMeshes;

		const aiScene *m_Scene;

		friend class Renderer;
	};
}