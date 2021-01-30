#include "Inspector.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "SemperEngine/Graphics/ImGui/ImGuiLayer.h"

#include "SemperEngine/Core/EngineApplication.h"
#include "SemperEngine/Scene/Components.h"


namespace SemperEngine
{
	template<>
	void Inspector::DrawComponentInfo<IdentificationComponent>(Entity entity);
	template<>
	void Inspector::DrawComponentInfo<TransformComponent>(Entity entity);
	template<>
	void Inspector::DrawComponentInfo<SpriteComponent>(Entity entity);
	template<>
	void Inspector::DrawComponentInfo<SceneCameraComponent>(Entity entity);
	template<>
	void Inspector::DrawComponentInfo<NativeScripComponent>(Entity entity);


	Inspector::Inspector(SharedPtr<Scene> handle) : 
		m_SceneHandle(handle)
	{
	}

	void Inspector::OnImGui(Entity selectedEntity)
	{
		ImGui::Begin("Inspector");
		
		if (selectedEntity && selectedEntity.Has<IdentificationComponent>())
			DrawComponentInfo<IdentificationComponent>(selectedEntity);
		
		if(selectedEntity && selectedEntity.Has<TransformComponent>())
			DrawComponentInfo<TransformComponent>(selectedEntity);
		
		if (selectedEntity && selectedEntity.Has<SpriteComponent>())
			DrawComponentInfo<SpriteComponent>(selectedEntity);

		if(selectedEntity && selectedEntity.Has<SceneCameraComponent>())
			DrawComponentInfo<SceneCameraComponent>(selectedEntity);

		if (selectedEntity && selectedEntity.Has<NativeScripComponent>())
			DrawComponentInfo<NativeScripComponent>(selectedEntity);

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

	template<>
	void Inspector::DrawComponentInfo<IdentificationComponent>(Entity entity)
	{
		auto &idc = entity.Get<IdentificationComponent>();
		UUID entityUUID = idc.ID;

		char buffer[64];
		std::memset(buffer, 0, 64);
		std::memcpy(buffer, idc.name.c_str(), idc.name.length());

		float buttonSize = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		float nameWidth = ImGui::GetContentRegionAvail().x - buttonSize;

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 5.0f));
		ImGui::SetNextItemWidth(nameWidth);
		if (ImGui::InputText("##Name", buffer, 64))
			idc.name = std::string(buffer);

		ImGui::SameLine();
		if (ImGui::Button("...", ImVec2(buttonSize, buttonSize)))
			ImGui::OpenPopup("Settings");

		ImGui::PopStyleVar();	// Item spacing

		if (ImGui::BeginPopup("Settings"))
		{
			if (ImGui::BeginMenu("Add Component"))
			{
				if (ImGui::MenuItem("Transform"))
					if (!entity.Has<TransformComponent>())
						entity.Add<TransformComponent>(TransformComponent {});

				if (ImGui::MenuItem("Sprite"))
					if (!entity.Has<SpriteComponent>())
						entity.Add<SpriteComponent>(SpriteComponent {});

				if (ImGui::MenuItem("Scene Camera"))
					if (!entity.Has<SceneCameraComponent>())
						entity.Add<SceneCameraComponent>(SceneCameraComponent {});

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

	template<>
	void Inspector::DrawComponentInfo<TransformComponent>(Entity entity)
	{
		auto &transform = entity.Get<TransformComponent>().transform;
		auto [translation, rotation, scale] = entity.Get<TransformComponent>().GetTranslationRotationScale();

		if (ImGui::CollapsingHeader("Transform Component"))
		{
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(1))
				ImGui::OpenPopup("Component Options##Transform");

			auto UUID = entity.Get<IdentificationComponent>().ID;

			Vec3 rotationDeg = glm::degrees(rotation);

			ImGui::PushID((int) (U64) UUID);
			if (DrawSliderFloat3(" Translation", 100.0f, translation, 0.0f))
				transform.SetTranslation(translation);
			if (DrawSliderFloat3(" Rotation", 100.0f, rotationDeg, 0.0f))
				transform.SetRotation(glm::radians(rotationDeg));
			if (DrawSliderFloat3(" Scale", 100.0f, scale, 1.0f))
				transform.SetScale(scale);
			ImGui::PopID();
		}
		else if (ImGui::IsItemHovered() && ImGui::IsMouseDown(1))
			ImGui::OpenPopup("Component Options##Transform");

		if (ImGui::BeginPopup("Component Options##Transform"))
		{
			if (ImGui::MenuItem("Remove Component"))
				entity.Remove<TransformComponent>();

			ImGui::EndPopup();
		}
	}

	template<>
	void Inspector::DrawComponentInfo<SpriteComponent>(Entity entity)
	{
		auto &sprite = entity.Get<SpriteComponent>();

		if (ImGui::CollapsingHeader("Sprite Component"))
		{
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(1))
				ImGui::OpenPopup("Component Options##Sprite");

			Vec4 color = Vec4(sprite.GetColor());
			if (ImGui::ColorEdit4("Sprite Color", &color[0]))
				sprite.SetColor(color);
			auto Texture = sprite.sprite.GetTexture();
			if (Texture)
				ImGui::Image((void *) Texture->GetHandle(), ImVec2(64.0f, 64.0f));
			else ImGui::Image(nullptr, ImVec2(64.0f, 64.0f));
			if (ImGui::IsItemClicked())
			{
				std::string filename = EngineApplication::Instance().OpenFile("");
				if (filename != "")
				{
					SharedPtr<Texture2D> texture;
					texture.reset(Texture2D::Create(filename));
					sprite.SetTexture(texture);
				}
			}
		}
		else {
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(1))
				ImGui::OpenPopup("Component Options##Sprite");
		}

		if (ImGui::BeginPopup("Component Options##Sprite"))
		{
			if (ImGui::MenuItem("Remove Component##Sprite"))
				entity.Remove<SpriteComponent>();

			ImGui::EndPopup();
		}
	}
	template<>
	void Inspector::DrawComponentInfo<SceneCameraComponent>(Entity entity)
	{
		auto &camera = entity.Get<SceneCameraComponent>();

		if (ImGui::CollapsingHeader("Scene Camera"))
		{
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(1))
				ImGui::OpenPopup("Component Options##Scene Camera");

			ImGui::Checkbox("Primary", &camera.primary);
		}
		else {
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(1))
				ImGui::OpenPopup("Component Options##Scene Camera");
		}

		if (ImGui::BeginPopup("Component Options##Scene Camera"))
		{
			if (ImGui::MenuItem("Remove Component##OrthoCamera"))
				entity.Remove<SceneCameraComponent>();

			ImGui::EndPopup();
		}
	}
	template<>
	void Inspector::DrawComponentInfo<NativeScripComponent>(Entity entity)
	{
		if (ImGui::CollapsingHeader("Native Script"))
		{
		}
	}
}