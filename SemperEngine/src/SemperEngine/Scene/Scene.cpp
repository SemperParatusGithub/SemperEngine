#include "Precompiled.h"
#include "Scene.h"

#include <imgui.h>

#include "Entity.h"
#include "Components.h"


namespace SemperEngine
{
	Entity Scene::CreateEntity()
	{
		ECS::EntityHandle handle = m_World.CreateEntity();

		return Entity(handle, this);
	}

	void Scene::RemoveEntity(Entity entity)
	{
		m_World.RemoveEntity(entity.GetHandle());
	}

	ECS::World Scene::GetWorld()
	{
		return m_World;
	}

	void Scene::OnImGuiRender()
	{
		ImGui::Begin("Hierarchy");
		ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);


		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::BeginMenu("Create"))
			{
				if (ImGui::MenuItem("Entity"))
				{
					auto newEntity = CreateEntity();
					m_ActiveEntityHandle = newEntity.GetHandle();
				}
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}

		// Render Entities
		for (auto &entityHandle : m_World)
		{
			if (m_World.Has<IdentificationComponent>(entityHandle))
			{
				auto id = m_World.Get<IdentificationComponent>(entityHandle);

				ImGui::PushID((int) entityHandle);

				bool isActive = entityHandle == m_ActiveEntityHandle;

				ImGui::SetNextTreeNodeOpen(isActive);

				ImGui::CollapsingHeader(id.name.c_str());

				if (ImGui::IsItemClicked())
					m_ActiveEntityHandle = isActive ? ECS::NullEntity : entityHandle;
				ImGui::PopID();
			}
		}

		ImGui::PopFont();
		ImGui::End();

		ImGui::Begin("Inspector");
		for (auto &entityHandle : m_World)
		{
			if (entityHandle == m_ActiveEntityHandle)
			{
				if (m_World.Has<IdentificationComponent>(entityHandle))
				{
					auto &id = m_World.Get<IdentificationComponent>(entityHandle);
					char buffer[64];
					std::memset(buffer, 0, 64);
					std::memcpy(buffer, id.name.c_str(), id.name.length());
					ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() / 2.0f);
					if (ImGui::InputText("##Name", buffer, 64))
						id.name = std::string(buffer);

					ImGui::SameLine();
					ImGui::Text("ID: %llx", id.ID);
				}
			}
		}
		ImGui::End();
	}
}