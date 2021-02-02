#include "Precompiled.h"
#include "LogConsole.h"

#include "SemperEngine/Graphics/ImGui/ImGuiLayer.h"


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
		ImGui::PushFont(ImGuiLayer::GetFont(OPEN_SANS_REGULAR));	// OpenSans-Regular

		if (m_Buffer.size() >= 1000)
			m_Buffer.erase(m_Buffer.begin(), m_Buffer.begin() + 500);

		float filterSize = ImGui::GetContentRegionAvailWidth() - 163.0f;

		ImGui::SetNextItemWidth(filterSize);
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
			ImGui::Separator();

			ImGui::PushStyleColor(ImGuiCol_Text, LogBase::SeverityToImGuiColor(Severity::Info));
			ImGui::PushStyleColor(ImGuiCol_CheckMark, LogBase::SeverityToImGuiColor(Severity::Info));
			ImGui::Checkbox("Info", &m_ShowInfos);
			ImGui::PopStyleColor(2);

			ImGui::PushStyleColor(ImGuiCol_Text, LogBase::SeverityToImGuiColor(Severity::Warn));
			ImGui::PushStyleColor(ImGuiCol_CheckMark, LogBase::SeverityToImGuiColor(Severity::Warn));
			ImGui::Checkbox("Warn", &m_ShowWarnings);
			ImGui::PopStyleColor(2);

			ImGui::PushStyleColor(ImGuiCol_Text, LogBase::SeverityToImGuiColor(Severity::Error));
			ImGui::PushStyleColor(ImGuiCol_CheckMark, LogBase::SeverityToImGuiColor(Severity::Error));
			ImGui::Checkbox("Error", &m_ShowErrors);
			ImGui::PopStyleColor(2);

			ImGui::PushStyleColor(ImGuiCol_Text, LogBase::SeverityToImGuiColor(Severity::Critical));
			ImGui::PushStyleColor(ImGuiCol_CheckMark, LogBase::SeverityToImGuiColor(Severity::Critical));
			ImGui::Checkbox("Critical", &m_ShowCriticals);
			ImGui::PopStyleColor(2);

			ImGui::EndPopup();
		}

		ImGui::Spacing();

		ImGui::BeginChild("Log Messages", { 0.0f, 0.0f }, true);
		for (const auto &elem : m_Buffer)
		{
			switch (elem.severity)
			{
				case Severity::Info:		if (!m_ShowInfos)		continue; break;
				case Severity::Warn:		if (!m_ShowWarnings)	continue; break;
				case Severity::Error:		if (!m_ShowErrors)		continue; break;
				case Severity::Critical:	if (!m_ShowCriticals)	continue; break;
			}

			// Check for filter
			if (!std::string(m_InputBuffer).empty())
				if (elem.message.find(std::string(m_InputBuffer)) == std::string::npos)
					continue;
			
			// Draw Text
			{
				ImGui::PushStyleColor(ImGuiCol_Text, LogBase::SeverityToImGuiColor(elem.severity));

				char buf[1024];
				sprintf_s(buf, 1024, "[%s][%s] %s: %s\n", elem.time.c_str(), LogBase::LoggerTypeToString(elem.type).c_str(),
					LogBase::SeverityToString(elem.severity).c_str(), elem.message.c_str());
				ImGui::TextWrapped("%s", buf);

				ImGui::PopStyleColor();
			}

			if (m_EnableAutoscroll)
				ImGui::SetScrollHereY(1.0f);
		}
		ImGui::EndChild();		// Log messages
		ImGui::PopFont();		// OpenSans-Regular

		ImGui::End();			// Log Console
	}
}