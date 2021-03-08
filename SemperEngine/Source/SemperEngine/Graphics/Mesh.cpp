#include "Precompiled.h"
#include "Mesh.h"

#include <assimp/LogStream.hpp>
#include <assimp/DefaultLogger.hpp>

#include "SemperEngine/Graphics/Renderers/Renderer.h"


namespace SemperEngine
{
	static const uint32_t s_MeshImportFlags =
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_SortByPType |           
		aiProcess_GenNormals |           
		aiProcess_GenUVCoords |           
		aiProcess_OptimizeMeshes |        
		aiProcess_ValidateDataStructure;  

	struct LogStream : public Assimp::LogStream
	{
		static void Initialize()
		{
			if (Assimp::DefaultLogger::isNullLogger())
			{
				Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
				Assimp::DefaultLogger::get()->attachStream(new LogStream, Assimp::Logger::Err | Assimp::Logger::Warn | Assimp::Logger::Info | Assimp::Logger::Debugging);
			}
		}

		virtual void write(const char *message) override
		{
			SE_CORE_INFO("Assimp: %s", message);
		}
	};

	Vec3 AssimpVec3ToVec3(ConstRef<aiVector3D> vector)
	{
		return Vec3 {
			vector.x,
			vector.y,
			vector.z
		};
	}
	Vec2 AssimpVec2ToVec2(ConstRef<aiVector2D> vector)
	{
		return Vec2 {
			vector.x,
			vector.y
		};
	}

	SubMesh::SubMesh(const std::vector<Vertex> &vertices, const std::vector<U32> &indices) : 
		m_Vertices(vertices),
		m_Indices(indices)
	{
		PreparePipeline();
	}
	SubMesh::~SubMesh()
	{
	}
	void SubMesh::PreparePipeline()
	{
		// Create VertexBuffer and set all Attributes
		m_VertexBuffer = VertexBuffer::Create(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex), BufferUsage::Static);
		m_VertexBuffer->AddAttribute({ "a_Position", VertexFormat::Float3, false });
		m_VertexBuffer->AddAttribute({ "a_Normal", VertexFormat::Float3, false });
		m_VertexBuffer->AddAttribute({ "a_Tangent", VertexFormat::Float3, false });
		m_VertexBuffer->AddAttribute({ "a_Bitangent", VertexFormat::Float3, false });
		m_VertexBuffer->AddAttribute({ "a_TexCoords", VertexFormat::Float2, false });

		// Create Index Buffer
		m_IndexBuffer = IndexBuffer::Create(m_Indices.data(), IndexFormat::Uint32, m_Indices.size() * sizeof(U32), BufferUsage::Static);

		// Create Vertex Array
		m_VertexArray = VertexArray::Create(m_VertexBuffer.get(), m_IndexBuffer.get());

		// Create Shader
		m_MeshShader = Renderer::GetShaderManager()->GetShader("PBR");
	}

	Mesh::Mesh() : 
		m_Filepath(""),
		m_IsLoaded(false),
		m_Scene(nullptr)
	{
	}
	Mesh::Mesh(ConstRef<std::string> filepath) : 
		m_Filepath(filepath),
		m_IsLoaded(false),
		m_Scene(nullptr)
	{
		Load(filepath);
	}
	Mesh::~Mesh()
	{
	}
	void Mesh::Load(ConstRef<std::string> filepath)
	{
		SE_CORE_INFO("Loading Mesh: %s", filepath.c_str());

		LogStream::Initialize();

		m_Filepath = filepath;
		m_SubMeshes.clear();

		UniquePtr<Assimp::Importer> m_Importer;
		m_Importer = MakeUnique<Assimp::Importer>();
		m_Scene = m_Importer->ReadFile(filepath, s_MeshImportFlags);

		if (!m_Scene || !m_Scene->HasMeshes())
			SE_ASSERT_MSG(false, "Failed to load Mesh");

		if (m_Scene->mAnimations != nullptr)
			SE_ASSERT_MSG(false, "Animations currently not supported");

		ProcessNode(m_Scene->mRootNode);

		SE_CORE_INFO("Sub Meshes: %d", m_SubMeshes.size());

		m_IsLoaded = true;
	}

	void Mesh::ProcessNode(aiNode *node)
	{
		for (uint32_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = m_Scene->mMeshes[node->mMeshes[i]];
			m_SubMeshes.push_back(ProcessMesh(mesh));
		}
		for (uint32_t i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i]);
		}
	}
	SubMesh Mesh::ProcessMesh(aiMesh *mesh)
	{		
		// Vertices
		std::vector<Vertex> vertices;

		for (uint32_t i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex currentVertex;

			// Position
			currentVertex.position = AssimpVec3ToVec3(mesh->mVertices[i]);

			// Normals
			if (mesh->HasNormals())
				currentVertex.normal = AssimpVec3ToVec3(mesh->mNormals[i]);

			// Tangents & Bitangents
			if (mesh->HasTangentsAndBitangents())
			{
				currentVertex.tangent = AssimpVec3ToVec3(mesh->mTangents[i]);
				currentVertex.bitangent = AssimpVec3ToVec3(mesh->mBitangents[i]);
			}

			// Texture Coords
			if (mesh->HasTextureCoords(0))
			{
				Vec2 textureCoords = {
					mesh->mTextureCoords[0][i].x,
					mesh->mTextureCoords[0][i].y
				};

				currentVertex.texCoords = textureCoords;
			}

			vertices.push_back(currentVertex);
		}

		// Indices
		std::vector<U32> indices;

		for (uint32_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (uint32_t j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		return SubMesh { vertices, indices };
	}
}