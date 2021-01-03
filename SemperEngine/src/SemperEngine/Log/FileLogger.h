#pragma once
#include "LogBase.h"
#include "SemperEngine/Core/Types.h"

#include <fstream>
#include <sstream>


namespace SemperEngine
{
	class FileLogger
	{
	public:
		FileLogger(ConstRef<std::string> outputPath) : 
			m_OutputPath(outputPath)
		{
		}
		~FileLogger() = default;

		inline void LogMessage(ConstRef<std::string> messageString)
		{
			m_Buffer.push_back(messageString);
		}

		inline void Flush()
		{
			m_OutputStream.open(m_OutputPath);

			for (const auto &string : m_Buffer)
			{
				m_OutputStream << string << std::endl;
			}

			m_OutputStream.flush();
			m_OutputStream.close();
		}

	private:
		std::string m_OutputPath;
		std::vector<std::string> m_Buffer;
		std::ofstream m_OutputStream;
	};
}