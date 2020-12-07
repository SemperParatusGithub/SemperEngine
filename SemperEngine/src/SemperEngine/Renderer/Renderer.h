#pragma once

#include "Backend.h"
#include <glm/glm.hpp>
#include "VertexArray.h"
#include "Shader.h"

namespace SemperEngine
{
	class Renderer
	{
	public:
		static void Init(Backend *backend);
		static void Shutdown();

		static void SetClearColor(const glm::vec4 &clearColor);
		static void SetViewport(float x, float y, float width, float height);
		static void Clear();

		static void DrawIndexed(VertexArray *vertexArray, Shader *shader);
	};
}