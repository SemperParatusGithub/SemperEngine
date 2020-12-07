#include "ApplicationLayer.h"

class Application : public SemperEngine::EngineApplication
{
public:
	static SemperEngine::EngineApplication *CreateApplication(const std::string &name)
	{
		auto *app = new (std::nothrow) SemperEngine::EngineApplication(name);
		SE_ASSERT_MSG(app, "Failed to Create Application");

		app->Instance().PushLayer(new ApplicationLayer());

		return app;
	}
};