#include "pch.h"
#include "Renderer.h"

#include <glad/glad.h>

namespace SemperEngine
{
	Backend *s_CurrentBackend = nullptr;

	void Renderer::Init(Backend *backend)
	{
		s_CurrentBackend = backend;
		s_CurrentBackend->Init();
	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::SetClearColor(const glm::vec4 &clearColor)
	{
		s_CurrentBackend->SetClearColor(clearColor);
	}

	void Renderer::SetViewport(float x, float y, float width, float height)
	{
		s_CurrentBackend->SetViewport(x, y, width, height);
	}

	void Renderer::Clear()
	{
		s_CurrentBackend->Clear();
	}

	void Renderer::DrawIndexed(VertexArray *vertexArray, Shader *shader)
	{
		s_CurrentBackend->DrawIndexed(vertexArray, shader);
	}
}