#include "Hierarchy.h"


namespace Widget
{
	Hierarchy::Hierarchy()
	{
	}
	Hierarchy::~Hierarchy()
	{
	}

	void Hierarchy::Open()
	{
		m_IsOpen = true;
	}
	void Hierarchy::Close()
	{
		m_IsOpen = false;
	}

	ConstRef<std::string> Hierarchy::GetName() const
	{
		return m_Name;
	}

	bool Hierarchy::IsOpen() const
	{
		return m_IsOpen;
	}

	void Hierarchy::OnRender()
	{
		SE_ASSERT(m_Scene);
		if (m_IsOpen)
		{
			ImGui::Begin("Hierarchy", &m_IsOpen, ImGuiWindowFlags_None);
			ImGui::PushFont(ImGuiLayer::GetFont(OPEN_SANS_REGULAR));

			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::BeginMenu("Create"))
				{
					if (ImGui::MenuItem("Entity"))
					{
						m_SelectedEntity = m_Scene->CreateEntity();
					}
					ImGui::EndMenu();
				}
				ImGui::EndPopup();
			}

			auto view = m_Scene->GetRegistry().view<IdentificationComponent>();

			for (auto entity : view)
			{
				Entity currentEntity = Entity(entity, m_Scene.get());
				bool isActive = currentEntity == m_SelectedEntity;

				auto &idc = view.get<IdentificationComponent>(entity);

				ImGui::PushID((int) idc.ID);
				if (ImGui::Selectable(idc.name.c_str(), &isActive))
					m_SelectedEntity = currentEntity;
				ImGui::PopID();
			}


			ImGui::PopFont();
			ImGui::End();
		}
	}

	void Hierarchy::SetScene(SharedPtr<Scene> scene)
	{
		m_Scene = scene;
	}
	SharedPtr<Scene> Hierarchy::GetScene()
	{
		return m_Scene;
	}

	void Hierarchy::SetSelectedEntity(Entity entity)
	{
		m_SelectedEntity = entity;
	}
	Entity Hierarchy::GetSelectedEntity()
	{
		return m_SelectedEntity;
	}
}