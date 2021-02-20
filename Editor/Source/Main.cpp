#include "Editor.h"


int main(int argc, char *argv[])
{
	SemperEngine::CoreSystem::Initialize();

	auto *Editor = Editor::CreateApplication("Semper Editor");

	Editor->Run();

	delete Editor;

	SemperEngine::CoreSystem::Shutdown();

	return EXIT_SUCCESS;
}