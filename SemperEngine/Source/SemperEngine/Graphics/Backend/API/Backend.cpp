#include "Precompiled.h"
#include "Backend.h"
#include "SemperEngine/Log/Log.h"
#include "SemperEngine/Core/Assert.h"

#include "SemperEngine/Graphics/Backend/OpenGL/GLBackend.h"


namespace SemperEngine
{
	Backend::API Backend::s_RenderAPI = Backend::API::OpenGL;

	Backend *Backend::Create()
	{
		if (s_RenderAPI == API::None)
		{
			SE_ASSERT_MSG(false, "RenderAPI::None is currently not supported");
			return nullptr;
		}
		if (s_RenderAPI == API::DirectX)
		{
			SE_ASSERT_MSG(false, "DirectX is currently not supported");
			return nullptr;
		}
		if (s_RenderAPI == API::OpenGL)
		{
			return new GLBackend();
		}
		else if (s_RenderAPI == API::Vulkan)
		{
			SE_ASSERT_MSG(false, "Vulkan is currently not supported");
			return nullptr;
		}
		else {
			SE_ASSERT_MSG(false, "Unknown API");
			return nullptr;
		}
	}

	Backend::API Backend::GetRenderAPI()
	{
		return s_RenderAPI;
	}
}