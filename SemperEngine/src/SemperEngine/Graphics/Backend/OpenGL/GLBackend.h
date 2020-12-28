#pragma once
#include "SemperEngine/Graphics/Backend/API/Backend.h"


namespace SemperEngine
{
	class GLBackend : public Backend
	{
	public:
		GLBackend() = default;
		~GLBackend() = default;

		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4 &clearColor) override;
		virtual void SetViewport(float x, float y, float width, float height) override;
		virtual void Clear() override;

		virtual void DrawIndexed(VertexArray *vertexArray, Shader *shader);
	};
}