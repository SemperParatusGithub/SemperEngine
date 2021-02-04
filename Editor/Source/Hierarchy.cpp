#include "Hierarchy.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "SemperEngine/Graphics/ImGui/ImGuiLayer.h"

#include "SemperEngine/Scene/Components.h"


namespace SemperEngine
{
	Hierarchy::Hierarchy(SharedPtr<Scene> handle) : 
		m_SceneHandle(handle)
	{
	}

	void Hierarchy::OnImGui()
	{
		ImGui::Begin("Hierarchy");
		ImGui::PushFont(ImGuiLayer::GetFont(OPEN_SANS_REGULAR));

		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::BeginMenu("Create"))
			{
				if (ImGui::MenuItem("Entity"))
				{
					m_SelectedEntity = m_SceneHandle->CreateEntity();
				}
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}

		auto view = m_SceneHandle->GetRegistry().view<IdentificationComponent>();

		for (auto entity : view)
		{
			Entity currentEntity = Entity(entity, m_SceneHandle.get());
			bool isActive = currentEntity == m_SelectedEntity;

			auto &idc = view.get<IdentificationComponent>(entity);

			ImGui::PushID((int) idc.ID);
			if (ImGui::Selectable(idc.name.c_str(), &isActive))
				m_SelectedEntity = currentEntity;
			ImGui::PopID();
		}


		ImGui::PopFont();
		ImGui::End();	// Hierarchy
	}
}