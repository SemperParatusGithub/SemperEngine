#pragma once
#include "SemperEngine/Core/Types.h"


namespace SemperEngine
{
	class Filesystem
	{
	public:
		// Returns empty string when failed
		static std::string OpenFileDialog(const char *filter);
		static std::string SaveFileDialog(const char *filter);

		static std::string ReadFile(ConstRef<std::string> filepath);
		static void WriteToFile(ConstRef<std::string> filepath, ConstRef<std::string> data);
	};
}