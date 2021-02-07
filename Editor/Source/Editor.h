#include "EditorLayer.h"


class Editor : public SemperEngine::EngineApplication
{
public:
	static SemperEngine::EngineApplication *CreateApplication(const std::string &name)
	{
		auto *app = new (std::nothrow) SemperEngine::EngineApplication(name, 1600u, 900u);
		SE_ASSERT_MSG(app, "Failed to Create Application");

		app->Instance().GetWindow().SetMinimumSize(1280u, 720u);
		app->Instance().PushLayer(new EditorLayer());

		return app;
	}
};