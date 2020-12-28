#include "Precompiled.h"
#include "Renderer.h"

#include "Batcher2D.h"

#include <glad/glad.h>


namespace SemperEngine
{
	Backend *s_CurrentBackend = nullptr;

	void Renderer::Init(Backend *backend)
	{
		s_CurrentBackend = backend;
		s_CurrentBackend->Init();

		Batcher2D::Init();
	}

	void Renderer::Shutdown()
	{
		Batcher2D::Shutdown();
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