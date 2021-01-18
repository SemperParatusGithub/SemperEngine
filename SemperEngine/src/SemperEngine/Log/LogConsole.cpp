#include "Precompiled.h"
#include "LogConsole.h"


namespace SemperEngine
{
	LogConsole::LogConsole() : 
		m_EnableAutoscroll(true),
		m_ShowInfos(true), m_ShowErrors(true), m_ShowWarnings(true), m_ShowCriticals(true)
	{
		std::memset(m_InputBuffer, 0, sizeof(m_InputBuffer));
	}
	LogConsole::~LogConsole()
	{
	}

	void LogConsole::LogMessage(ConstRef<LogElement> element)
	{
		m_Buffer.push_back(element);
	}
	void LogConsole::Clear()
	{
		m_Buffer.clear();
	}

	void LogConsole::OnImGuiRender()
	{
		ImGui::Begin("Log Console");
		ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);	// OpenSans-Regular

		if (m_Buffer.size() >= 1000)
			m_Buffer.erase(m_Buffer.begin(), m_Buffer.begin() + 500);

		ImGui::SetNextItemWidth(ImGui::GetWindowSize().x * 0.45f);
		ImGui::InputText("Filter", m_InputBuffer, 256);

		ImGui::SameLine();
		if (ImGui::Button("Clear"))
			Clear();

		ImGui::SameLine();
		if (ImGui::Button("Options"))
			ImGui::OpenPopup("Options");

		if (ImGui::BeginPopup("Options"))
		{
			ImGui::Checkbox("Autoscroll", &m_EnableAutoscroll);
			ImGui::Checkbox("Info", &m_ShowInfos);
			ImGui::Checkbox("Warn", &m_ShowWarnings);
			ImGui::Checkbox("Error", &m_ShowErrors);
			ImGui::Checkbox("Critical", &m_ShowCriticals);
			ImGui::EndPopup();
		}

		ImGui::Spacing();

		ImGui::BeginChild("Log Messages", { 0.0f, 0.0f }, true);
		for (const auto &elem : m_Buffer)
		{
			// if the message doesn't contain the input string of the filter skip
			if (!std::string(m_InputBuffer).empty())
				if (elem.message.find(std::string(m_InputBuffer)) == std::string::npos)
					continue;

			switch (elem.severity)
			{
				case Severity::Info:		if (!m_ShowInfos)		continue; break;
				case Severity::Warn:		if (!m_ShowWarnings)	continue; break;
				case Severity::Error:		if (!m_ShowErrors)		continue; break;
				case Severity::Critical:	if (!m_ShowCriticals)	continue; break;
			}
			
			SetLogColor(elem.severity);

			char buf[1024];
			sprintf_s(buf, 1024, "[%s][%s] %s: %s\n", elem.time.c_str(), LogBase::LoggerTypeToString(elem.type).c_str(),
				LogBase::SeverityToString(elem.severity).c_str(), elem.message.c_str());
			ImGui::TextWrapped("%s", buf);

			ImGui::PopStyleColor();    // Pop style color that was set by SetLogColor()

			// Enable/disable auto scroll afterwards because the current message has to be displayed before
			if (m_EnableAutoscroll)
				ImGui::SetScrollHereY(1.0f);
		}
		ImGui::EndChild();    // Log messages
		ImGui::PopFont();

		ImGui::End();    // Log Console
	}

	void LogConsole::SetLogColor(Severity severity)
	{
		switch (severity)
		{
			case Severity::Info:	 ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f, 0.80f, 0.40f, 1.00f));	break;
			case Severity::Warn:	 ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 0.83f, 0.00f, 1.00f));	break;
			case Severity::Error:	 ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 0.40f, 0.40f, 1.00f));	break;
			case Severity::Critical: ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.40f, 0.00f, 0.00f, 1.00f));	break;
		}
	}
}