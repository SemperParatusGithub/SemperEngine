#include "Objects.h"


namespace Widget
{
	Objects::Objects()
	{
	}
	Objects::~Objects()
	{
	}

	void Objects::Open()
	{
		m_IsOpen = true;
	}
	void Objects::Close()
	{
		m_IsOpen = false;
	}

	ConstRef<std::string> Objects::GetName() const
	{
		return m_Name;
	}

	bool Objects::IsOpen() const
	{
		return m_IsOpen;
	}

	void Objects::OnRender()
	{
		static Object obj { Object::Cube };

		if (m_IsOpen)
		{
			ImGui::Begin(m_Name.c_str(), &m_IsOpen, ImGuiWindowFlags_None);
			DrawObject("Cube", obj);
			ImGui::End();
		}
	}

	void Objects::DrawObject(const char *label, Object &obj)
	{
		// ImGui::Image((ImTextureID)m_CubeImage->GetRendererID(), ImVec2(30, 30));
		// ImGui::SameLine();
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Selectable(label);

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
		{
			// ImGui::Image((ImTextureID)m_CubeImage->GetRendererID(), ImVec2(20, 20));
			// ImGui::SameLine();

			ImGui::Text(label);

			ImGui::SetDragDropPayload("payload", &obj, sizeof(Object));
			ImGui::EndDragDropSource();
		}

	}
}