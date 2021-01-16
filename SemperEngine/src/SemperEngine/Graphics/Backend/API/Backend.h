#pragma once
#include "SemperEngine/Core/Defines.h"

#include "VertexArray.h"
#include "Shader.h"

#include <glm/glm.hpp>


namespace SemperEngine
{
	class Backend
	{
	public:
		Backend() = default;
		virtual ~Backend() = default;

		enum class API
		{
			None = -1,
			DirectX,
			OpenGL,
			Vulkan
		};

		static Backend *Create();
		static API GetRenderAPI(); 

	private:
		virtual void Init() = 0;

		virtual void SetClearColor(ConstRef<glm::vec4> clearColor) = 0;
		virtual void SetViewport(float x, float y, float width, float height) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray, ConstRef<SharedPtr<Shader>> shader) = 0;

	private:
		static API s_RenderAPI;
		friend class Renderer;
	};
}