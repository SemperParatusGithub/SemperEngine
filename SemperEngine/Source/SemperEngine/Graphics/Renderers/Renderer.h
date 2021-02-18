#pragma once

#include "SemperEngine/Graphics/Backend/API/Backend.h"
#include "SemperEngine/Graphics/Backend/API/VertexArray.h"
#include "SemperEngine/Graphics/Backend/API/Shader.h"

#include <glm/glm.hpp>


namespace SemperEngine
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void SetClearColor(const glm::vec4 &clearColor);
		static void SetViewport(float x, float y, float width, float height);
		static void Clear();

		static void OnImGui();

		static void DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray, ConstRef<SharedPtr<Shader>> shader);
		static void DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray, ConstRef<SharedPtr<Shader>> shader, U32 count);
	};
}