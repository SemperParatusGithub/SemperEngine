#pragma once
#include "LogBase.h"
#include "SemperEngine/Core/Types.h"

#include "../imgui/imgui.h"


// Currently no command input is supported
// In the future functions like AddCommand() and GetCommandStatus() will be added


namespace SemperEngine
{
	class LogConsole
	{
	public:
		LogConsole();
		~LogConsole();

		void LogMessage(ConstRef<LogElement> element);
		void Clear();

		void OnImGuiRender();

	private:
		std::vector<LogElement> m_Buffer; 
		char m_InputBuffer[256];
		bool m_EnableAutoscroll;
		bool m_ShowInfos, m_ShowErrors, m_ShowWarnings, m_ShowCriticals;
	};
}