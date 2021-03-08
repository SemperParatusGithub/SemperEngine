#include "Precompiled.h"
#include "SceneRenderer.h"

#include "SemperEngine/Graphics/Backend/API/Framebuffer.h"
#include "SemperEngine/Graphics/Mesh.h"
#include "SemperEngine/Graphics/Transform.h"

#include "Renderer.h"


namespace SemperEngine
{
	struct MeshObject
	{
		SharedPtr<Mesh> mesh;
		Transform transform;
	};
	struct SceneRenderData
	{
		SceneInfo currentSceneInfo;
		SharedPtr<Framebuffer> mainFramebuffer;

		SharedPtr<Shader> rasterShader;

		std::vector<MeshObject> meshDrawList;
	};

	static SceneRenderData s_SceneRenderData;


	void SceneRenderer::Init()
	{
		FramebufferInfo fbi;
		fbi.width = 1280;
		fbi.height = 720;
		s_SceneRenderData.mainFramebuffer = Framebuffer::Create(fbi);
		s_SceneRenderData.rasterShader = Shader::Create(ShaderManager::LoadFromFile("Assets/Shaders/Raster.shader"));
	}
	void SceneRenderer::Shutdown()
	{
	}

	void SceneRenderer::BeginScene(ConstRef<SceneInfo> sceneInfo)
	{
		s_SceneRenderData.currentSceneInfo = sceneInfo;
	}
	void SceneRenderer::EndScene()
	{
		s_SceneRenderData.mainFramebuffer->OnResize(s_SceneRenderData.currentSceneInfo.viewportWidth,
			s_SceneRenderData.currentSceneInfo.viewportHeight);

		// Render
		s_SceneRenderData.mainFramebuffer->Bind();
		Renderer::Clear();

		Transform rasterTransform;
		rasterTransform.Rotate(Vec3(glm::radians(90.0f), 0.0f, 0.0f));
		rasterTransform.SetScale(Vec3(25.0f, 25.0f, 25.0f));
		rasterTransform.SetTranslation(Vec3(0.0f, -0.0000001f, 0.0f));

		s_SceneRenderData.rasterShader->Bind();
		s_SceneRenderData.rasterShader->SetUniformFloat3("u_GridColor", Vec3(0.2f, 0.2f, 0.2f));
		s_SceneRenderData.rasterShader->SetUniformFloat("u_Segments", 32.0f);

		Renderer::SubmitQuad(rasterTransform, s_SceneRenderData.currentSceneInfo.projectionViewMatrix, s_SceneRenderData.rasterShader);

		auto &meshShader = Renderer::GetShaderManager()->GetShader("PBR");
		meshShader->Bind();
		meshShader->SetUniformMat4f("u_ProjectionView", s_SceneRenderData.currentSceneInfo.projectionViewMatrix);
		meshShader->SetUniformFloat3("u_CameraPosition", s_SceneRenderData.currentSceneInfo.cameraPosition);
		meshShader->SetUniformFloat3("u_DirectionalLights.Direction", Vec3(glm::radians(30.0f), glm::radians(20.0f), 0.0f));
		meshShader->SetUniformFloat3("u_DirectionalLights.Radiance", Vec3(0.1f));
		meshShader->SetUniformFloat("u_DirectionalLights.Multiplier", 10.0f);

		for (auto &meshObj : s_SceneRenderData.meshDrawList)
		{
			meshShader->SetUniformFloat3("u_AlbedoColor", Vec3(0.7f, 0.2f, 0.4f));
			meshShader->SetUniformFloat("u_Metalness", 0.9f);
			meshShader->SetUniformFloat("u_Roughness", 0.3f);
			Renderer::SubmitMesh(meshObj.mesh, meshObj.transform, meshShader);
		}

		// Clear mesh draw list
		s_SceneRenderData.meshDrawList.clear();

		s_SceneRenderData.mainFramebuffer->UnBind();
	}

	void SceneRenderer::SubmitMesh(SharedPtr<Mesh> mesh, ConstRef<Transform> transform)
	{
		s_SceneRenderData.meshDrawList.push_back({ mesh,transform });
	}

	void *SceneRenderer::GetFinalFramebufferColorAttachmentHandle()
	{
		return s_SceneRenderData.mainFramebuffer->GetColorAttachmentHandle();
	}
}