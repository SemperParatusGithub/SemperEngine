#include "Precompiled.h"
#include "Renderer.h"

#include "Batcher2D.h"

#include "SemperEngine/Core/EngineApplication.h"

#include <glad/glad.h>


namespace SemperEngine
{
	Backend *s_CurrentBackend = nullptr;

	void Renderer::Init()
	{
		s_CurrentBackend = Backend::Create();
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

	void Renderer::OnImGui()
	{
		ImGui::Begin("Renderer");

		const auto &caps = s_CurrentBackend->GetCapabilities();
		if (ImGui::CollapsingHeader("General"))
		{
			ImGui::Text("Framerate: %.2f FPS", EngineApplication::Instance().GetFramerate());
			ImGui::Text("Frametime: %.2f ms", EngineApplication::Instance().GetFrametime());
			ImGui::Separator();
			ImGui::Text("Render API: %s", caps.renderAPI.c_str());
			ImGui::Text("Vendor: %s", caps.vendor.c_str());
			ImGui::Text("Renderer: %s", caps.renderAPI.c_str());
			ImGui::Text("Version: %s", caps.version.c_str());
			ImGui::Separator();
			ImGui::Text("Max Samples: %d", caps.maxSamples);
			ImGui::Text("Max Textures: %d", caps.maxTextureUnits);
			ImGui::Text("Max Anisotropy: %.2f", caps.maxAnisotropy);
		}

		const auto &metrics = Batcher2D::GetMetrics();
		if (ImGui::CollapsingHeader("Batcher2D Metrics"))
		{
			ImGui::Text("Batches: %d", metrics.batches);
			ImGui::Text("Vertices: %d", metrics.vertices);
			ImGui::Text("Indices: %d", metrics.indices);
			ImGui::Text("Triangles: %d", metrics.triangles);
		}
		Batcher2D::ResetMetrics();

		auto &io = ImGui::GetIO();
		if (ImGui::CollapsingHeader("ImGui Metrics"))
		{
			ImGui::Text("Vertices: %d", io.MetricsRenderVertices);
			ImGui::Text("Indices: %d", io.MetricsRenderIndices);
			ImGui::Text("%d active windows (%d visible)", io.MetricsActiveWindows, io.MetricsRenderWindows);
			ImGui::Text("Triangles: %d", metrics.triangles);
		}

		if (ImGui::CollapsingHeader("Texture Viewer"))
		{
			static U32 index = 0;
			ImGui::Image(reinterpret_cast<void *>(index), ImVec2(128.0f, 128.0f), ImVec2 { 0, 1 }, ImVec2 { 1, 0 });
			ImGui::InputInt("Index", reinterpret_cast<int *>(&index), 1, 10);
		} 

		ImGui::End();
	}

	void Renderer::DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray, ConstRef<SharedPtr<Shader>> shader)
	{
		s_CurrentBackend->DrawIndexed(vertexArray, shader);
	}

	void Renderer::DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray, ConstRef<SharedPtr<Shader>> shader, U32 count)
	{
		s_CurrentBackend->DrawIndexed(vertexArray, shader, count);
	}
}