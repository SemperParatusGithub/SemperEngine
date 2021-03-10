#pragma once

#include "SemperEngine/Core/Types.h"

#include "SemperEngine/Graphics/Backend/API/Backend.h"
#include "SemperEngine/Graphics/Backend/API/VertexArray.h"
#include "SemperEngine/Graphics/Backend/API/Shader.h"

#include <glm/glm.hpp>

#include "SemperEngine/Graphics/Mesh.h"
#include "SemperEngine/Graphics/Transform.h"


namespace SemperEngine
{
	class EditorCamera;
	struct CameraInfo;

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void SetClearColor(const glm::vec4 &clearColor);
		static void SetViewport(float x, float y, float width, float height);
		static void SetRenderMode(Backend::RenderMode mode);
		static void Clear();

		static void OnImGui();

		static ConstRef<SharedPtr<ShaderManager>> GetShaderManager();

		static void SubmitQuad(ConstRef<Transform> transform, ConstRef<Mat4> projectionView, ConstRef<SharedPtr<Shader>> shader);
		static void SubmitMesh(SharedPtr<Mesh> mesh, ConstRef<Transform> transform, ConstRef<CameraInfo> info);

		static void DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray);
		static void DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray, ConstRef<SharedPtr<Shader>> shader, U32 count);
	};
}