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
		struct Capabilities
		{
			std::string renderAPI;
			std::string vendor;
			std::string renderer;
			std::string version;

			int maxSamples = 0;
			int maxTextureUnits = 0;
			float maxAnisotropy = 0.0f;
		};

		static Backend *Create();

		static API GetRenderAPI(); 
		static Capabilities GetCapabilities();

	private:
		virtual void Init() = 0;

		virtual void SetClearColor(ConstRef<Vec4> clearColor) = 0;
		virtual void SetViewport(float x, float y, float width, float height) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray, ConstRef<SharedPtr<Shader>> shader) = 0;
		virtual void DrawIndexed(ConstRef<SharedPtr<VertexArray>> vertexArray, ConstRef<SharedPtr<Shader>> shader, U32 count) = 0;

	protected:
		static API s_RenderAPI;
		static Capabilities s_Capabilities;

		friend class Renderer;
	};
}