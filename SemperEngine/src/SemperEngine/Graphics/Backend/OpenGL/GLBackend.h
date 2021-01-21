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

		virtual void SetClearColor(ConstRef<glm::vec4> clearColor) override;
		virtual void SetViewport(float x, float y, float width, float height) override;
		virtual void Clear() override;

		virtual std::string GetRenderAPIString() override;
		virtual std::string GetVendor() override;
		virtual std::string GetRenderer() override;
		virtual std::string GetVersion() override;

		virtual void DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray, ConstRef<SharedPtr<Shader>> shader);
	};
}