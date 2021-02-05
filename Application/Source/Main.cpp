#include "Application.h"

int main(int argc, char *argv[])
{
	SemperEngine::Log::Init(true, false);

	/* Startup */
	auto *App = Application::CreateApplication("Semper Application");

	/* Runtime */
	App->Run();

	/* Shutdown */
	delete App;

	return EXIT_SUCCESS;
}