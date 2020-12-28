#include "Precompiled.h"
#include "Batcher2D.h"

#include "Renderer.h"		// includes VertexArray.h and Shader.h
#include "SemperEngine/Graphics/Backend/API/Texture.h"


namespace SemperEngine
{
	struct QuadVertex
	{
		Vec4 position;
		Vec4 color;
		Vec2 texCoords;
		float texIndex;			// 0 = whiteTexture --> FlatColor
	};

	struct RenderData
	{
		VertexArray *vertexArray = nullptr;
		VertexBuffer *vertexBuffer = nullptr;
		IndexBuffer *indexBuffer = nullptr;

		QuadVertex *buffer = nullptr;
		QuadVertex *bufferPtr = nullptr;

		U32 indexCount = 0;

		glm::vec4 vertexPositions[4];
		glm::vec2 textureCoords[4];

		Shader *shader = nullptr;

		Texture2D *whiteTexture;
		std::array<const Texture2D *, MaxCombinedTextureUnits> textures;
	};

	static RenderData s_RenderData;


	void Batcher2D::Init()
	{
		// Initialize quad data
		s_RenderData.buffer = new QuadVertex[MaxVertexCount];
		s_RenderData.vertexBuffer = VertexBuffer::Create(nullptr, MaxVertexCount * sizeof(QuadVertex), BufferUsage::Dynamic);

		s_RenderData.vertexBuffer->AddAttribute({ "a_Position", VertexFormat::Float4, false });
		s_RenderData.vertexBuffer->AddAttribute({ "a_Color", VertexFormat::Float4, false });
		s_RenderData.vertexBuffer->AddAttribute({ "a_TexCoords", VertexFormat::Float2, false });
		s_RenderData.vertexBuffer->AddAttribute({ "a_TexIndex", VertexFormat::Float1, false });

		U32 *indices = new U32[MaxIndexCount];
		U32 offset = 0;
		for (int i = 0; i < MaxIndexCount; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}
		s_RenderData.indexBuffer = IndexBuffer::Create(indices, IndexFormat::Uint32, MaxIndexCount * sizeof(U32), BufferUsage::Static);

		s_RenderData.vertexArray = VertexArray::Create(s_RenderData.vertexBuffer, s_RenderData.indexBuffer);

		s_RenderData.vertexPositions[0] = { -0.5f, -0.5f,  0.0f,  1.0f };
		s_RenderData.vertexPositions[1] = { 0.5f, -0.5f,  0.0f,  1.0f };
		s_RenderData.vertexPositions[2] = { 0.5f,  0.5f,  0.0f,  1.0f };
		s_RenderData.vertexPositions[3] = { -0.5f,  0.5f,  0.0f,  1.0f };

		s_RenderData.textureCoords[0] = { 0.0f, 0.0f };
		s_RenderData.textureCoords[1] = { 1.0f, 0.0f };
		s_RenderData.textureCoords[2] = { 1.0f, 1.0f };
		s_RenderData.textureCoords[3] = { 0.0f, 1.0f };

		// General Initialization
		s_RenderData.shader = Shader::Create(ShaderManager::LoadFromFile("Batch.shader"));

		s_RenderData.whiteTexture = Texture2D::Create("WhiteTexture.png");

		for (auto &texture : s_RenderData.textures)
			texture = s_RenderData.whiteTexture;

		int samplers[MaxCombinedTextureUnits];
		for (U32 i = 0; i < MaxCombinedTextureUnits; i++)
			samplers[i] = i;

		s_RenderData.shader->Bind();
		s_RenderData.shader->SetUniformIntArray("u_Samplers", samplers, MaxCombinedTextureUnits);
	}
	void Batcher2D::Shutdown()
	{
	}

	void Batcher2D::BeginScene(ConstRef<OrthographicCamera> camera)
	{
		s_RenderData.indexCount = 0;
		s_RenderData.bufferPtr = s_RenderData.buffer;	
		
		s_RenderData.shader->Bind();
		s_RenderData.shader->SetUniformMat4f("u_ProjectionView", camera.GetProjectionView());
	}
	void Batcher2D::EndScene()
	{
		Flush();
	}
	void Batcher2D::Flush()
	{
		for (std::size_t i = 0; i < s_RenderData.textures.size(); i++)
			s_RenderData.textures[i]->Bind(static_cast<U32>(i));

		for (std::size_t i = 0; i < s_RenderData.textures.size(); i++)
			s_RenderData.textures[i] = s_RenderData.whiteTexture;

		U32 size = static_cast<U32>(reinterpret_cast<U8 *>(s_RenderData.bufferPtr) - reinterpret_cast<U8 *>(s_RenderData.buffer));
		s_RenderData.vertexBuffer->SetData(s_RenderData.buffer, size);

		Renderer::DrawIndexed(s_RenderData.vertexArray, s_RenderData.shader);
	}

	void Batcher2D::DrawQuad(ConstRef<Transform> transform, ConstRef<Vec4> color)
	{
		if (s_RenderData.indexCount >= MaxIndexCount)
		{
			Flush();
			BeginScene();
		}

		float textureIndex = 0.0f;	// Render with white texture (flat color)

		for (U32 i = 0; i < 4; i++)
		{
			s_RenderData.bufferPtr->position = transform.GetTransform() * s_RenderData.vertexPositions[i];
			s_RenderData.bufferPtr->color = color;
			s_RenderData.bufferPtr->texCoords = s_RenderData.textureCoords[i];
			s_RenderData.bufferPtr->texIndex = textureIndex;
			s_RenderData.bufferPtr++;
		}
		s_RenderData.indexCount += 6;
	}

	void Batcher2D::DrawQuad(ConstRef<Transform> transform, Texture2D *texture, ConstRef<glm::vec4> tintColor)
	{
		if (s_RenderData.indexCount >= MaxIndexCount)
		{
			Flush();
			BeginScene();
		}

		float textureIndex = 0.0f;

		for (std::size_t i = 1; i < s_RenderData.textures.size(); i++)
		{
			if (s_RenderData.textures[i]->GetHandle() == texture->GetHandle()) {
				textureIndex = static_cast<float>(i);
				break;
			}
			else if (s_RenderData.textures[i]->GetHandle() == s_RenderData.whiteTexture->GetHandle()) {
				textureIndex = static_cast<float>(i);
				s_RenderData.textures[i] = texture;
				break;
			}
		}

		for (U32 i = 0; i < 4; i++)
		{
			s_RenderData.bufferPtr->position = transform.GetTransform() * s_RenderData.vertexPositions[i];
			s_RenderData.bufferPtr->color = tintColor;
			s_RenderData.bufferPtr->texCoords = s_RenderData.textureCoords[i];
			s_RenderData.bufferPtr->texIndex = textureIndex;
			s_RenderData.bufferPtr++;
		}

		s_RenderData.indexCount += 6;
	}

	void Batcher2D::BeginScene()
	{
		s_RenderData.indexCount = 0;
		s_RenderData.bufferPtr = s_RenderData.buffer;
	}
}