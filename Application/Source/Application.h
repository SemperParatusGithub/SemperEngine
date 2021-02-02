#pragma once
#include "ApplicationLayer.h"
#include "TestLayer.h"


class Application : public SemperEngine::EngineApplication
{
public:
	static SemperEngine::EngineApplication *CreateApplication(const std::string &name)
	{
		auto *app = new SemperEngine::EngineApplication(name);

		app->Instance().PushLayer(new ApplicationLayer());
		//app->Instance().PushLayer(new TestLayer());

		return app;
	}
};