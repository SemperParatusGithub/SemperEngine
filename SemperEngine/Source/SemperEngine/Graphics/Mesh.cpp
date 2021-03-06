#include "Precompiled.h"
#include "Mesh.h"

#include <assimp/LogStream.hpp>
#include <assimp/DefaultLogger.hpp>

#include "SemperEngine/Graphics/Renderers/Renderer.h"
#include "SemperEngine/Scene/Components.h"


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
			std::string msg = std::string(message);
			std::replace(msg.begin(), msg.end(), '\n', ' ');
			SE_CORE_INFO("Assimp: %s", msg.c_str());
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

	Mat4 AssimpMat4ToMat4(ConstRef<aiMatrix4x4> matrix)
	{
		Mat4 result;
		//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
		result[0][0] = matrix.a1; result[1][0] = matrix.a2; result[2][0] = matrix.a3; result[3][0] = matrix.a4;
		result[0][1] = matrix.b1; result[1][1] = matrix.b2; result[2][1] = matrix.b3; result[3][1] = matrix.b4;
		result[0][2] = matrix.c1; result[1][2] = matrix.c2; result[2][2] = matrix.c3; result[3][2] = matrix.c4;
		result[0][3] = matrix.d1; result[1][3] = matrix.d2; result[2][3] = matrix.d3; result[3][3] = matrix.d4;
		return result;
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
		{
			SE_CORE_ERROR("Failed to load mesh: %s", m_Filepath.c_str());
		}
		else if (m_Scene->mAnimations)
		{
			SE_CORE_ERROR("Animations currently not supported: %s", m_Filepath.c_str());
		}
		else {
			m_Material = MakeShared<Material>("Base Material");

			// Process mesh recursively
			ProcessNode(m_Scene->mRootNode, Mat4(1.0f));

			SE_CORE_INFO("Total sub meshes: %d", m_SubMeshes.size());
			SE_CORE_INFO("Total mesh vertices: %d", m_Vertices.size());
			SE_CORE_INFO("Total mesh indices: %d", m_Indices.size());

			SE_CORE_INFO("Preparing Pipeline");
			PreparePipeline();
			SE_CORE_INFO("Pipeline was succesfully prepared");

			m_IsLoaded = true;
		}
	}

	bool Mesh::IsLoaded() const
	{
		return m_IsLoaded;
	}

	SharedPtr<Material> Mesh::GetMaterial()
	{
		return m_Material;
	}

	std::vector<SubMesh> &Mesh::GetSubMeshes()
	{
		return m_SubMeshes;
	}

	void Mesh::ProcessNode(aiNode *node, ConstRef<Mat4> parentTransform)
	{
		Mat4 transform = parentTransform * AssimpMat4ToMat4(node->mTransformation);

		for (uint32_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = m_Scene->mMeshes[node->mMeshes[i]];
			m_SubMeshes.push_back(ProcessMesh(mesh, transform));
		}
		for (uint32_t i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], transform);
		}
	}
	SubMesh Mesh::ProcessMesh(aiMesh *mesh, ConstRef<Mat4> meshTransform)
	{		
		SubMesh subMesh;
		subMesh.transform = meshTransform;
		subMesh.vertexOffset = m_Vertices.size();
		subMesh.indexOffset = m_Indices.size();

		// Vertices
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

			m_Vertices.push_back(currentVertex);
		}

		// Indices
		for (uint32_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			SE_ASSERT(face.mNumIndices == 3);

			for (uint32_t j = 0; j < face.mNumIndices; j++)
				m_Indices.push_back(face.mIndices[j]);
		}

		// handle offsets
		subMesh.vertexCount = m_Vertices.size() - subMesh.vertexOffset;
		subMesh.indexCount = m_Indices.size() - subMesh.indexOffset;


		// Materials
		aiMaterial *aiMaterial= m_Scene->mMaterials[mesh->mMaterialIndex];

		U32 materialIndex = m_Material->GetSubMaterials().size();
		std::string materialName = aiMaterial->GetName().C_Str();
		bool materialFound = false;

		for (int i = 0; i < m_Material->GetSubMaterials().size(); i++)
		{
			if (m_Material->GetSubMaterials()[i].GetName() == materialName)
			{
				materialIndex = i;
				materialFound = true;
			}
		}

		if (!materialFound)
		{
			SubMaterial subMaterial(materialName);

			aiColor3D aiColor;
			aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor);

			float shininess, metalness, roughness;
			if (aiMaterial->Get(AI_MATKEY_SHININESS, shininess) != aiReturn_SUCCESS)
				shininess = 80.0f; // Default value

			if (aiMaterial->Get(AI_MATKEY_REFLECTIVITY, metalness) != aiReturn_SUCCESS)
				metalness = 0.0f;

			roughness = 1.0f - glm::sqrt(shininess / 100.0f);

			PBRMaterialParameters params = {
				Vec3(aiColor.r, aiColor.g, aiColor.b),	// Albedo
				metalness,								// Metalness	
				roughness								// Roughness
			};

			SE_CORE_INFO("Mesh Debug Info: %s: AlbedoColor: %.2f, %.2f, %.2f", aiMaterial->GetName().C_Str(), aiColor.r, aiColor.g, aiColor.b);
			SE_CORE_INFO("Mesh Debug Info: %s: Metalness: %.2f", aiMaterial->GetName().C_Str(), metalness);
			SE_CORE_INFO("Mesh Debug Info: %s: Roughness: %.2f", aiMaterial->GetName().C_Str(), roughness);

			subMaterial.GetPBRMaterialParameters() = params;

			// TODO: Normal, metalness and roughness maps
			PBRMaterialTextures textures = {
				false, false, false, false,
				Texture2D::Create(),
				Texture2D::Create(),
				Texture2D::Create(),
				Texture2D::Create()
			};
			
			aiString aiTexturePath;
			if (aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aiTexturePath) == AI_SUCCESS)
			{
				std::filesystem::path path = m_Filepath;
				auto parentPath = path.parent_path();
				parentPath /= std::string(aiTexturePath.data);
				std::string texturePath = parentPath.string();
				SE_CORE_INFO("Albedo Texture filepath = %s", texturePath.c_str());
				auto texture = Texture2D::Create(texturePath);
				textures.albedoTexture = texture;
				if(texture->IsLoaded())
					textures.useAlbedoTexture = true;
			}

			subMaterial.GetPBRMaterialTextures() = textures;


			m_Material->AddSubMaterial(subMaterial);
		}

		subMesh.materialIndex = materialIndex;

		return subMesh;
	}

	void Mesh::PreparePipeline()
	{
		// Create VertexBuffer and set all Attributes
		m_VertexBuffer = VertexBuffer::Create(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex), BufferUsage::Static);
		m_VertexBuffer->AddAttribute({ "a_Position",  VertexFormat::Float3, false });
		m_VertexBuffer->AddAttribute({ "a_Normal",	  VertexFormat::Float3, false });
		m_VertexBuffer->AddAttribute({ "a_Tangent",	  VertexFormat::Float3, false });
		m_VertexBuffer->AddAttribute({ "a_Bitangent", VertexFormat::Float3, false });
		m_VertexBuffer->AddAttribute({ "a_TexCoords", VertexFormat::Float2, false });

		// Create Index Buffer
		m_IndexBuffer = IndexBuffer::Create(m_Indices.data(), IndexFormat::Uint32, m_Indices.size() * sizeof(U32), BufferUsage::Static);

		// Create Vertex Array
		m_VertexArray = VertexArray::Create(m_VertexBuffer.get(), m_IndexBuffer.get());
	}
}