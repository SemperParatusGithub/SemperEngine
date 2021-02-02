#include "Precompiled.h"
#include "Shader.h"

#include "Backend.h"
#include "SemperEngine/Graphics/Backend/OpenGL/GLShader.h"


namespace SemperEngine
{
	Shader *Shader::Create(ConstRef<ShaderManager::ShaderSource> shaderSource)
	{
		switch (Backend::GetRenderAPI())
		{
		case Backend::API::DirectX:
			SE_ASSERT_MSG(false, "DirectX not supported");
			return nullptr;

		case Backend::API::None:
			SE_ASSERT_MSG(false, "API::None not supported");
			return nullptr;

		case Backend::API::OpenGL:
			return new GLShader(shaderSource);

		case Backend::API::Vulkan:
			SE_ASSERT_MSG(false, "Vulkan not supported");
			return nullptr;
		}

		SE_ASSERT_MSG(false, "Unknown Render API");
		return nullptr;
	}
}