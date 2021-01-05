#pragma once
#include "SemperEngine/Core/Types.h"
#include "LogBase.h"

#include <fstream>
#include <sstream>


namespace SemperEngine
{
	class FileLogger
	{
	public:
		FileLogger(ConstRef<std::string> outputPath);
		~FileLogger();

		void LogMessage(ConstRef<LogElement> element);
		void Flush();

	private:
		std::string m_OutputPath;
		std::vector<std::string> m_Buffer;
		std::ofstream m_OutputStream;
	};
}