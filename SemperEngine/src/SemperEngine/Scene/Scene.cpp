#include "Precompiled.h"
#include "Scene.h"

#include <imgui.h>
#include <imgui_internal.h>

#include "Entity.h"


namespace SemperEngine
{
	Entity Scene::CreateEntity()
	{
		auto handle = m_World.CreateEntity();
		auto entity = Entity(handle, this);

		// Add default components
		entity.Add<IdentificationComponent>(IdentificationComponent { "Entity", {} });
		entity.Add<TransformComponent>(TransformComponent {});

		return entity;
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

				if (ImGui::Selectable(id.name.c_str(), &isActive))
					m_ActiveEntityHandle = entityHandle;

				ImGui::PopID();
			}
		}

		ImGui::PopFont();
		ImGui::End();

		ImGui::Begin("Inspector");
		for (auto &entityHandle : m_World)
			if (entityHandle == m_ActiveEntityHandle)
				DrawInspectorComponentInfo(Entity(entityHandle, this));
		ImGui::End();
	}

	void Scene::DrawInspectorComponentInfo(Entity entity)
	{
		if (entity.Has<IdentificationComponent>())
		{
			auto &id = entity.Get<IdentificationComponent>();
			char buffer[64];
			std::memset(buffer, 0, 64);
			std::memcpy(buffer, id.name.c_str(), id.name.length());
			ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() / 2.0f);
			if (ImGui::InputText("##Name", buffer, 64))
				id.name = std::string(buffer);

			ImGui::SameLine();
			ImGui::Text("ID: %llx", id.ID);
		}
		if (entity.Has<TransformComponent>())
		{
			auto UUID = entity.Get<IdentificationComponent>().ID;

			auto &transform = entity.Get<TransformComponent>().transform;
			auto [translation, rotation, scale] = entity.Get<TransformComponent>().GetTranslationRotationScale();
			if (ImGui::CollapsingHeader("Transform Component"))
			{
				ImGui::PushID((uint64_t)UUID);
				if (DrawSliderFloat3(" Translation", 100.0f, translation, 0.0f))
					transform.SetTranslation(translation);
				if (DrawSliderFloat3(" Rotation", 100.0f, rotation, 0.0f))
					transform.SetRotation(rotation);
				if (DrawSliderFloat3(" Scale", 100.0f, scale, 1.0f))
					transform.SetScale(scale);
				ImGui::PopID();
			}
		}
	}

	bool Scene::DrawSliderFloat3(ConstRef<std::string> name, float labelWidth, Vec3 &vector, float resetValue)
	{
		bool valuesChanged = false;

		auto openSansRegular = ImGui::GetIO().Fonts->Fonts[1];
		auto openSansBold = ImGui::GetIO().Fonts->Fonts[2];

		float regionWidth = ImGui::GetContentRegionAvail().x - labelWidth;
		float sz = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

		ImVec2 buttonSize = { sz, sz };
		float sliderSize = regionWidth / 3.0f - buttonSize.x;

		ImGui::PushID(name.c_str());

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2 { 0.0f, 5.0f });
		ImGui::PushFont(openSansRegular);

		ImGui::Text(name.c_str());
		ImGui::SameLine(labelWidth);

		ImGui::SetNextItemWidth(sliderSize);
		if (ImGui::DragFloat("##x", &vector[0], 0.1f, 0.0f, 0.0f, "%.3f"))
			valuesChanged = true;

		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 { 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 { 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 { 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(openSansBold);
		if (ImGui::Button("X", buttonSize)) {
			vector.x = resetValue;
			valuesChanged = true;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::SetNextItemWidth(sliderSize);
		if (ImGui::DragFloat("##y", &vector[1], 0.1f, 0.0f, 0.0f, "%.3f"))
			valuesChanged = true;

		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 { 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 { 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 { 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(openSansBold);
		if (ImGui::Button("Y", buttonSize)) {
			vector.y = resetValue;
			valuesChanged = true;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::SetNextItemWidth(sliderSize);
		if (ImGui::DragFloat("##z", &vector[2], 0.1f, 0.0f, 0.0f, "%.3f"))
			valuesChanged = true;
		
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 { 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 { 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 { 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(openSansBold);
		if (ImGui::Button("Z", buttonSize)) {
			vector.z = resetValue;
			valuesChanged = true;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::PopFont();	// openSansRegular
		ImGui::PopStyleVar(2);	// Item Spacing, Frame Rounding

		ImGui::PopID();

		return valuesChanged;
	}
}