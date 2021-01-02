#include "Editor.h"


int main(int argc, char *argv[])
{
	SemperEngine::Log::Init();

	auto *Editor = Editor::CreateApplication("Semper Editor");

	Editor->Run();

	delete Editor;

	return EXIT_SUCCESS;
}