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

		bool showRaster = true;
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

	void SceneRenderer::OnImGui()
	{
		ImGui::Begin("Scene Renderer");
		ImGui::Checkbox("Raster", &s_SceneRenderData.showRaster);
		ImGui::End();
	}

	void SceneRenderer::BeginScene(ConstRef<SceneInfo> sceneInfo)
	{
		s_SceneRenderData.currentSceneInfo = sceneInfo;
	}
	void SceneRenderer::EndScene()
	{
		// Render
		s_SceneRenderData.mainFramebuffer->Bind();
		Renderer::Clear();

		if (s_SceneRenderData.showRaster)
		{
			Transform rasterTransform;
			rasterTransform.Rotate(Vec3(glm::radians(90.0f), 0.0f, 0.0f));
			rasterTransform.SetScale(Vec3(25.0f, 25.0f, 25.0f));
			rasterTransform.SetTranslation(Vec3(0.0f, -0.0000001f, 0.0f));

			s_SceneRenderData.rasterShader->Bind();
			s_SceneRenderData.rasterShader->SetUniformFloat3("u_GridColor", Vec3(0.2f, 0.2f, 0.2f));
			s_SceneRenderData.rasterShader->SetUniformFloat("u_Segments", 50.0f);

			Renderer::SubmitQuad(rasterTransform, s_SceneRenderData.currentSceneInfo.cameraInfo.projectionViewMatrix, s_SceneRenderData.rasterShader);
		}

		for (auto &meshObj : s_SceneRenderData.meshDrawList)
		{
			Renderer::SubmitMesh(meshObj.mesh, meshObj.transform, s_SceneRenderData.currentSceneInfo.cameraInfo);
		}

		// Clear mesh draw list
		s_SceneRenderData.meshDrawList.clear();

		s_SceneRenderData.mainFramebuffer->UnBind();
	}

	void SceneRenderer::OnResize(U32 viewportWidth, U32 viewportHeight)
	{
		s_SceneRenderData.mainFramebuffer->OnResize(viewportWidth, viewportHeight);
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