#pragma once

#include <glm/glm.hpp>
#include "SemperEngine/Graphics/Backend/API/Texture.h"

#include "SemperEngine/Graphics/Transform.h"
#include "SemperEngine/Graphics/Camera/OrthographicCamera.h"
#include "SemperEngine/Core/Types.h"


namespace SemperEngine
{
	static constexpr U32 MaxCombinedTextureUnits = 16;

	static constexpr U32 MaxTriangleCount = 1000;
	static constexpr U32 MaxTriangleVertexCount = MaxTriangleCount * 3;

	static constexpr U32 MaxQuadCount = MaxTriangleCount * 2;
	static constexpr U32 MaxVertexCount = MaxQuadCount * 4;
	static constexpr U32 MaxIndexCount = MaxQuadCount * 6;

	class Batcher2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(ConstRef<OrthographicCamera> camera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(ConstRef<Transform> transform, ConstRef<Vec4> color);
		static void DrawQuad(ConstRef<Transform> transform, Texture2D *texture, ConstRef<glm::vec4> tintColor = Vec4(1.0f));

	private:
		static void BeginScene();
	};
}