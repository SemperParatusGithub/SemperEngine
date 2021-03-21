#pragma once

#include "SemperEngine/Core/Types.h"
#include "SemperEngine/Scene/Scene.h"


namespace SemperEngine
{
	struct CameraInfo
	{
		Vec3 cameraPosition;
		Mat4 projectionViewMatrix;
	};
	struct SceneInfo
	{
		Scene *context;
		CameraInfo cameraInfo;
	};

	class Mesh;
	class Transform;

	class SceneRenderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnImGui();

		static void BeginScene(ConstRef<SceneInfo> sceneInfo);
		static void EndScene();

		static void OnResize(U32 viewportWidth, U32 viewportHeight);

		static void SubmitMesh(SharedPtr<Mesh> mesh, ConstRef<Transform> transform);

		static void *GetFinalFramebufferColorAttachmentHandle();
	};
}