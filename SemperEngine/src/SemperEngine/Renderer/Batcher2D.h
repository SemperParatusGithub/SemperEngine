#pragma once

#include <glm/glm.hpp>
#include "Texture.h"

#include "Camera/OrthographicCamera.h"
#include "SemperEngine/Core/Types.h"
#include "SemperEngine/Utils/Transform.h"


namespace SemperEngine
{
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