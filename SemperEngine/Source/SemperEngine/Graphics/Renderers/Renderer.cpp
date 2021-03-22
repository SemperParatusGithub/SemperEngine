#include "Precompiled.h"
#include "Renderer.h"

#include "Batcher2D.h"
#include "SceneRenderer.h"

#include "SemperEngine/Core/EngineApplication.h"

#include "SemperEngine/Graphics/Backend/API/Backend.h"
#include "SemperEngine/Graphics/Backend/API/VertexArray.h"
#include "SemperEngine/Graphics/Backend/API/Shader.h"

#include "SemperEngine/Graphics/Mesh.h"
#include "SemperEngine/Graphics/Transform.h"

// TODO: Remove me!!!
#include <glad/glad.h>


namespace SemperEngine
{
	Backend *s_CurrentBackend = nullptr;

	struct RenderData
	{
		SharedPtr<VertexArray> quadVertexArray;
		SharedPtr<VertexBuffer> quadVertexBuffer;
		SharedPtr<IndexBuffer> quadIndexBuffer;

		SharedPtr<ShaderManager> shaderManager;

		SharedPtr<Texture2D> whiteTexture;
		SharedPtr<Texture2D> emptyTexture; // = Checkerboard Texture
	};

	static RenderData s_RenderData;

	void Renderer::Init()
	{
		s_CurrentBackend = Backend::Create();
		s_CurrentBackend->Init();

		Batcher2D::Init();
		SceneRenderer::Init();

		float quadVertices[] = {
		  // Position				Tex Coords
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
		};
		U32 quadIndices[] = {
			0, 1, 2, 2, 3, 0
		};

		s_RenderData.quadVertexBuffer = VertexBuffer::Create(quadVertices, sizeof(quadVertices), BufferUsage::Static);
		s_RenderData.quadVertexBuffer->AddAttribute({ "a_Position", VertexFormat::Float3, false });
		s_RenderData.quadVertexBuffer->AddAttribute({ "a_TexCoords", VertexFormat::Float2, false });

		s_RenderData.quadIndexBuffer = IndexBuffer::Create(quadIndices, IndexFormat::Uint32, sizeof(quadIndices), BufferUsage::Static);
		s_RenderData.quadVertexArray = VertexArray::Create(s_RenderData.quadVertexBuffer.get(), s_RenderData.quadIndexBuffer.get());

		s_RenderData.shaderManager = MakeShared<ShaderManager>();

		s_RenderData.shaderManager->AddShaderFromFile("PBR", "Assets/Shaders/PBR.shader");

		LoadRequiredRendererAssets();
	}

	void Renderer::Shutdown()
	{
		Batcher2D::Shutdown();
	}

	void Renderer::SetClearColor(const glm::vec4 &clearColor)
	{
		s_CurrentBackend->SetClearColor(clearColor);
	}

	void Renderer::SetViewport(float x, float y, float width, float height)
	{
		s_CurrentBackend->SetViewport(x, y, width, height);
	}

	void Renderer::SetRenderMode(Backend::RenderMode mode)
	{
		s_CurrentBackend->SetRenderMode(mode);
	}

	void Renderer::Clear()
	{
		s_CurrentBackend->Clear();
	}

	ConstRef<SharedPtr<Texture2D>> Renderer::GetWhiteTexture()
	{
		return s_RenderData.whiteTexture;
	}
	ConstRef<SharedPtr<Texture2D>> Renderer::GetEmptyTexture()
	{
		return s_RenderData.emptyTexture;
	}

	void Renderer::OnImGui()
	{
		ImGui::Begin("Renderer");

		const auto &caps = s_CurrentBackend->GetCapabilities();
		if (ImGui::CollapsingHeader("General"))
		{
			ImGui::Text("Framerate: %.2f FPS", EngineApplication::Instance().GetFramerate());
			ImGui::Text("Frametime: %.2f ms", EngineApplication::Instance().GetFrametime());
			ImGui::Separator();
			ImGui::Text("Render API: %s", caps.renderAPI.c_str());
			ImGui::Text("Vendor: %s", caps.vendor.c_str());
			ImGui::Text("Renderer: %s", caps.renderAPI.c_str());
			ImGui::Text("Version: %s", caps.version.c_str());
			ImGui::Separator();
			ImGui::Text("Max Samples: %d", caps.maxSamples);
			ImGui::Text("Max Textures: %d", caps.maxTextureUnits);
			ImGui::Text("Max Anisotropy: %.2f", caps.maxAnisotropy);
		}

		// const auto &metrics = Batcher2D::GetMetrics();
		// if (ImGui::CollapsingHeader("Batcher2D Metrics"))
		// {
		// 	ImGui::Text("Batches: %d", metrics.batches);
		// 	ImGui::Text("Vertices: %d", metrics.vertices);
		// 	ImGui::Text("Indices: %d", metrics.indices);
		// 	ImGui::Text("Triangles: %d", metrics.triangles);
		// }
		// Batcher2D::ResetMetrics();

		auto &io = ImGui::GetIO();
		if (ImGui::CollapsingHeader("ImGui Metrics"))
		{
			ImGui::Text("Vertices: %d", io.MetricsRenderVertices);
			ImGui::Text("Indices: %d", io.MetricsRenderIndices);
			ImGui::Text("%d active windows (%d visible)", io.MetricsActiveWindows, io.MetricsRenderWindows);
			ImGui::Text("Active Allocations: %d", io.MetricsActiveAllocations);
		}

		ImGui::End();	// Renderer
	}

	ConstRef<SharedPtr<ShaderManager>> Renderer::GetShaderManager()
	{
		return s_RenderData.shaderManager;
	}

	void Renderer::SubmitQuad(ConstRef<Transform> transform, ConstRef<Mat4> projectionView, ConstRef<SharedPtr<Shader>> shader)
	{
		shader->Bind();
		shader->SetUniformMat4f("u_ProjectionView", projectionView);
		shader->SetUniformMat4f("u_Transform", transform.GetTransform());
		s_RenderData.quadVertexArray->Bind();
		DrawIndexed(s_RenderData.quadVertexArray, shader, 6);
	}

	void Renderer::SubmitMesh(SharedPtr<Mesh> mesh, ConstRef<Transform> transform, ConstRef<CameraInfo> info)
	{
		auto &material = mesh->m_Material;
		auto &shader = material->m_MaterialShader;

		shader->Bind();
		shader->SetUniformMat4f("u_ProjectionView", info.projectionViewMatrix);
		shader->SetUniformFloat3("u_CameraPosition", info.cameraPosition);
		shader->SetUniformFloat3("u_DirectionalLights.Direction", Vec3(glm::radians(30.0f), glm::radians(20.0f), 0.0f));
		shader->SetUniformFloat3("u_DirectionalLights.Radiance", Vec3(0.1f));
		shader->SetUniformFloat("u_DirectionalLights.Multiplier", 10.0f);

		mesh->m_VertexArray->Bind();
		mesh->m_IndexBuffer->Bind();

		for (auto &subMesh : mesh->m_SubMeshes)
		{
			auto &subMaterial = material->GetSubMaterials()[subMesh.materialIndex];

			auto &params = subMaterial.GetPBRMaterialParameters();
			shader->SetUniformFloat3("u_AlbedoColor", params.albedoColor);
			shader->SetUniformFloat("u_Metalness", params.metalness);
			shader->SetUniformFloat("u_Roughness", params.roughness);

			auto &textures = subMaterial.GetPBRMaterialTextures();
			if (textures.useAlbedoTexture)
			{
				shader->SetUniformInt("u_EnableAlbedoTexture", 1);
				textures.albedoTexture->Bind(0);
				shader->SetUniformInt("u_AlbedoTexture", 0);
			}

			shader->SetUniformMat4f("u_Transform", transform.GetTransform() * subMesh.transform);

			glDrawElementsBaseVertex(GL_TRIANGLES, subMesh.indexCount, GL_UNSIGNED_INT,
				(const void *) (sizeof(U32) * subMesh.indexOffset), subMesh.vertexOffset);
		}
	}

	void Renderer::DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray)
	{
		s_CurrentBackend->DrawIndexed(vertexArray);
	}

	void Renderer::DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray, ConstRef<SharedPtr<Shader>> shader, U32 count)
	{
		s_CurrentBackend->DrawIndexed(vertexArray, shader, count);
	}

	void Renderer::LoadRequiredRendererAssets()
	{
		s_RenderData.whiteTexture = Texture2D::Create("Assets/Textures/WhiteTexture.png");
		s_RenderData.emptyTexture = Texture2D::Create("Assets/Textures/EmptyTexture.png");
	}
}