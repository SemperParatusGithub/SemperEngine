#include "Hierarchy.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "SemperEngine/Graphics/ImGui/ImGuiLayer.h"


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

		for (auto &entityHandle : m_SceneHandle->GetWorld())
		{
			Entity currentEntity = Entity(entityHandle, m_SceneHandle.get());

			if (currentEntity.Has<IdentificationComponent>())
			{
				auto [name, uuid] = currentEntity.Get<IdentificationComponent>().GetNameID();
				bool isActive = currentEntity == m_SelectedEntity;

				ImGui::PushID((int) uuid);
				if (ImGui::Selectable(name.c_str(), &isActive))
					m_SelectedEntity = currentEntity;
				ImGui::PopID();
			}
		}

		ImGui::PopFont();
		ImGui::End();		// Hierarchy
	}
}