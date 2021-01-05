#include "Precompiled.h"
#include "FileLogger.h"


namespace SemperEngine
{
	FileLogger::FileLogger(ConstRef<std::string> outputPath) : 
		m_OutputPath(outputPath)
	{
	}
	FileLogger::~FileLogger()
	{
	}

	void FileLogger::LogMessage(ConstRef<LogElement> element)
	{
		char buf[1024];
		sprintf_s(buf, 1024, "[%s][%s] %s: %s\n", element.time.c_str(), LogBase::LoggerTypeToString(element.type).c_str(),
			LogBase::SeverityToString(element.severity).c_str(), element.message.c_str());
		m_Buffer.push_back(std::string(buf));
	}
	void FileLogger::Flush()
	{
		m_OutputStream.open(m_OutputPath);

		for (const auto &string : m_Buffer)
			m_OutputStream << string;

		m_OutputStream.flush();
		m_OutputStream.close();
	}
}