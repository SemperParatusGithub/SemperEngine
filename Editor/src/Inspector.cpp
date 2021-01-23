#include "Inspector.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "SemperEngine/Graphics/ImGui/ImGuiLayer.h"


namespace SemperEngine
{
	Inspector::Inspector(Scene *handle) : 
		m_SceneHandle(handle)
	{
	}

	void Inspector::OnImGui(Entity selectedEntity)
	{
		ImGui::Begin("Inspector");
		for (auto entityHandle : m_SceneHandle->GetWorld())
		{
			Entity currentEntity(entityHandle, m_SceneHandle);
			if (currentEntity == selectedEntity)
				if (DrawEntity(currentEntity))
					break;
		}
		ImGui::End();
	}

	bool Inspector::DrawSliderFloat3(ConstRef<std::string> name, float labelWidth, Vec3 &vector, float resetValue)
	{
		bool valuesChanged = false;

		auto openSansRegular = ImGuiLayer::GetFont(OPEN_SANS_REGULAR);
		auto openSansBold = ImGuiLayer::GetFont(OPEN_SANS_BOLD);

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
	
	bool Inspector::DrawEntity(Entity entity)
	{
		if (entity.Has<IdentificationComponent>())
		{
			auto &idc = entity.Get<IdentificationComponent>();
			UUID entityUUID = idc.ID;

			char buffer[64];
			std::memset(buffer, 0, 64);
			std::memcpy(buffer, idc.name.c_str(), idc.name.length());
			ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth() / 2.0f);

			float buttonSize = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			float nameWidth = ImGui::GetContentRegionAvail().x - buttonSize - 5.0f;

			ImGui::SetNextItemWidth(nameWidth);
			if (ImGui::InputText("##Name", buffer, 64))
				idc.name = std::string(buffer);

			ImGui::SameLine();
			if (ImGui::Button("...", ImVec2(buttonSize, buttonSize)))
				ImGui::OpenPopup("Settings");

			if (ImGui::BeginPopup("Settings"))
			{
				if (ImGui::BeginMenu("Add Component"))
				{
					if (ImGui::MenuItem("TransformComponent"));

					ImGui::EndMenu();
				}
				if (ImGui::MenuItem("Delete Entity"))
				{
					m_SceneHandle->DestroyEntity(entity);
				}			

				ImGui::EndPopup();
			}
			ImGui::Text(" UUID: %llx", entityUUID);
		}

		if(entity)
		{
			if (entity.Has<TransformComponent>())
			{
				auto &transform = entity.Get<TransformComponent>().transform;
				auto [translation, rotation, scale] = entity.Get<TransformComponent>().GetTranslationRotationScale();

				if (ImGui::CollapsingHeader("Transform Component"))
				{
					auto UUID = entity.Get<IdentificationComponent>().ID;

					ImGui::PushID((U64) UUID);
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
		else {
			return true;	// Entity was removed
		}
		return false;
	}
}
