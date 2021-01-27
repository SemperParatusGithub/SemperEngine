#pragma once
#include "SemperEngine/Graphics/Sprite.h"
#include "SemperEngine/Graphics/Transform.h"

#include "SemperEngine/Graphics/Camera/OrthographicCamera.h"
#include "SemperEngine/Graphics/Camera/EditorCamera.h"


namespace SemperEngine
{
	static constexpr U32 MaxCombinedTextureUnits = 16;

	static constexpr U32 MaxTriangleCount = 1000;
	static constexpr U32 MaxTriangleVertexCount = MaxTriangleCount * 3;

	static constexpr U32 MaxQuadCount = MaxTriangleCount * 2;
	static constexpr U32 MaxVertexCount = MaxQuadCount * 4;
	static constexpr U32 MaxIndexCount = MaxQuadCount * 6;


	struct Batcher2DMetrics
	{
		U32 batches = 0;
		U32 vertices = 0;
		U32 indices = 0;
		U32 triangles = 0;
	};

	class Batcher2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(ConstRef<Mat4> viewProjection);
		static void BeginScene(ConstRef<OrthographicCamera> camera);
		static void BeginScene(ConstRef<EditorCamera> camera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(ConstRef<Transform> transform, ConstRef<Vec4> color);
		static void DrawQuad(ConstRef<Transform> transform, ConstRef<SharedPtr<Texture2D>> texture, ConstRef<glm::vec4> tintColor = Vec4(1.0f));

		static void DrawSprite(ConstRef<Transform> transform, ConstRef<Sprite> sprite);

		static void ResetMetrics();
		static Batcher2DMetrics GetMetrics();

	private:
		static void BeginScene();
	};
}