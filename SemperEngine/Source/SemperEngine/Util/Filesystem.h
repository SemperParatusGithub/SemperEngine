#pragma once
#include <iostream>


namespace SemperEngine
{
	class Filesystem
	{
	public:
		// Returns empty string when failed
		static std::string OpenFileDialog(const char *filter);
		static std::string SaveFileDialog(const char *filter);
	};
}