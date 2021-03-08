#pragma once

#include "SemperEngine/Core/Types.h"
#include "SemperEngine/Scene/Scene.h"


namespace SemperEngine
{
	struct SceneInfo
	{
		Scene *context;
		U32 viewportWidth, viewportHeight;
		Vec3 cameraPosition;
		Mat4 projectionViewMatrix;
	};

	class Mesh;
	class Transform;

	class SceneRenderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(ConstRef<SceneInfo> sceneInfo);
		static void EndScene();

		static void SubmitMesh(SharedPtr<Mesh> mesh, ConstRef<Transform> transform);

		static void *GetFinalFramebufferColorAttachmentHandle();
	};
}