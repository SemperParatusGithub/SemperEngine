#include "Inspector.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "SemperEngine/Graphics/ImGui/ImGuiLayer.h"

#include "SemperEngine/Graphics/Renderers/Renderer.h"

#include "SemperEngine/Core/EngineApplication.h"
#include "SemperEngine/Scene/Components.h"

#include "SemperEngine/Util/Filesystem.h"


namespace Widget
{
	template<>
	void Inspector::DrawComponentInfo<IdentificationComponent>();
	template<>
	void Inspector::DrawComponentInfo<TransformComponent>();
	template<>
	void Inspector::DrawComponentInfo<SpriteComponent>();
	template<>
	void Inspector::DrawComponentInfo<SceneCameraComponent>();
	template<>
	void Inspector::DrawComponentInfo<NativeScriptComponent>();
	template<>
	void Inspector::DrawComponentInfo<MeshComponent>();


	Inspector::Inspector()
	{
	}
	Inspector::~Inspector()
	{
	}
	void Inspector::Open()
	{
	}
	void Inspector::Close()
	{
	}

	ConstRef<std::string> Inspector::GetName() const
	{
		return m_Name;
	}
	bool Inspector::IsOpen() const
	{
		return m_IsOpen;
	}

	void Inspector::OnRender()
	{
		if (m_IsOpen)
		{
			ImGui::Begin(m_Name.c_str(), &m_IsOpen, ImGuiWindowFlags_None);
			if (m_SelectedEntity)
				DrawComponents();
			ImGui::End();
		}
	}

	void Inspector::SetSelectedEntity(Entity entity)
	{
		m_SelectedEntity = entity;
	}
	Entity Inspector::GetSelectedEntity()
	{
		return m_SelectedEntity;
	}

	void Inspector::DrawComponents()
	{
		// Might delete the entity
		DrawComponentInfo<IdentificationComponent>();

		// Check if entity was deleted
		if (m_SelectedEntity)
		{
			DrawComponentInfo<TransformComponent>();
			DrawComponentInfo<SceneCameraComponent>();
			DrawComponentInfo<MeshComponent>();
		}
	}



	template<>
	void Inspector::DrawComponentInfo<IdentificationComponent>()
	{
		Entity entity = m_SelectedEntity;

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

				if (ImGui::MenuItem("Mesh"))
					if (!entity.Has<MeshComponent>())
						entity.Add<MeshComponent>(MeshComponent {});

				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Delete Entity"))
			{
				entity.Destroy();
			}

			ImGui::EndPopup();
		}
		ImGui::Text(" UUID: %llx", entityUUID);
	}

	template<>
	void Inspector::DrawComponentInfo<TransformComponent>()
	{
		auto &entity = m_SelectedEntity;
		if (!entity.Has<TransformComponent>())
			return;
		auto &transform = entity.Get<TransformComponent>().transform;
		auto [translation, rotation, scale] = entity.Get<TransformComponent>().GetTranslationRotationScale();

		if (ImGui::CollapsingHeader("Transform Component"))
		{
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(1))
				ImGui::OpenPopup("Component Options##Transform");

			auto UUID = entity.Get<IdentificationComponent>().ID;

			Vec3 rotationDeg = glm::degrees(rotation);

			ImGui::PushID((int) (U64) UUID);
			if (DrawSliderFloat3(" Translation", 110.0f, translation, 0.0f))
				transform.SetTranslation(translation);
			if (DrawSliderFloat3(" Rotation", 110.0f, rotationDeg, 0.0f))
				transform.SetRotation(glm::radians(rotationDeg));
			if (DrawSliderFloat3(" Scale", 110.0f, scale, 1.0f))
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
	void Inspector::DrawComponentInfo<SpriteComponent>()
	{
		Entity entity = m_SelectedEntity;
		auto &sprite = entity.Get<SpriteComponent>().sprite;

		if (ImGui::CollapsingHeader("Sprite Component"))
		{
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(1))
				ImGui::OpenPopup("Component Options##Sprite");

			Vec4 color = Vec4(sprite.GetColor());
			if (ImGui::ColorEdit4("Sprite Color", &color[0]))
				sprite.SetColor(color);

			if (!sprite.HasTexture() && !sprite.HasSpriteSheet())
			{
				if (ImGui::Button("Add Texture")) 
				{
					SharedPtr<Texture2D> emptyTexture = Texture2D::Create("Assets/Textures/EmptyTexture.png");
					sprite.SetTexture(emptyTexture);
				}
				ImGui::SameLine();
				if (ImGui::Button("Add SpriteSheet"))
				{
					SharedPtr<Texture2D> emptyTexture = Texture2D::Create("Assets/Textures/EmptyTexture.png");
					Vec2 textureSize = { static_cast<float>(emptyTexture->GetWidth()), static_cast<float>(emptyTexture->GetHeight()) };
					sprite.SetSpriteSheet(emptyTexture, Vec2(0.0f, 0.0f), textureSize);
				}
			}

			bool openFileDialogTexture = false;
			bool openFileDialogSpriteSheet = false;

			if (sprite.HasTexture())
			{
				ImGui::Image((void *) sprite.GetTexture()->GetHandle(), ImVec2(64.0f, 64.0f));
				if (ImGui::IsItemClicked())
				{
					std::string filename = Filesystem::OpenFileDialog("");
					if (filename != "")
					{
						SharedPtr<Texture2D> texture = Texture2D::Create(filename);
						sprite.SetTexture(texture);
					}
				}

				U32 width = sprite.GetTexture()->GetWidth(), height = sprite.GetTexture()->GetHeight();
				float ratio = (float) width / (float) height;

				ImGui::SameLine();
				ImGui::Text("Width: %d, Height %d\n Aspect Ratio: %.2f\n", width, height, ratio);

				ImGui::SameLine();
				if (ImGui::Button("Remove Texture"))
					sprite.RemoveTexture();
			}
			if (sprite.HasSpriteSheet())
			{
				float index[2] = { sprite.GetCellIndex().x, sprite.GetCellIndex().y };
				float size[2] = { sprite.GetCellSize().x, sprite.GetCellSize().y };

				ImGui::Text("SpriteSheet  Preview");

				ImGui::Image((void *) sprite.GetTexture()->GetHandle(), ImVec2(64.0f, 64.0f));
				if (ImGui::IsItemClicked())
				{
					std::string filename = Filesystem::OpenFileDialog("");
					if (filename != "")
					{
						SharedPtr<Texture2D> texture = Texture2D::Create(filename);
						Vec2 textureSize = { static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight()) };
						sprite.SetSpriteSheet(texture, Vec2(0.0f, 0.0f), textureSize);
					}
				}

				const auto &texCoords = sprite.GetTextureCoordinates();
				ImVec2 uv0 = { texCoords[0].x, texCoords[0].y };
				ImVec2 uv1 = { texCoords[2].x, texCoords[2].y };

				ImGui::SameLine();
				ImGui::Image((void *) sprite.GetTexture()->GetHandle(), ImVec2(64.0f, 64.0f), uv0, uv1);

				if (ImGui::SliderFloat2("Index", index, 0, 32, "%1.0f"))
					sprite.SetCellIndex({ index[0], index[1] });
				if (ImGui::SliderFloat2("Size", size, 0, 2048, "%1.0f"))
					sprite.SetCellSize({ size[0], size[1] });

				ImGui::SameLine();
				if (ImGui::Button("Remove SpriteSheet"))
					sprite.RemoveSpriteSheet();
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
	void Inspector::DrawComponentInfo<SceneCameraComponent>()
	{
		Entity entity = m_SelectedEntity;
		if (!entity.Has<SceneCameraComponent>())
			return;
		auto &cc = entity.Get<SceneCameraComponent>();
		auto &camera = cc.camera;

		if (ImGui::CollapsingHeader("Scene Camera"))
		{
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(1))
				ImGui::OpenPopup("Component Options##Scene Camera");

			ImVec2 region = ImGui::GetContentRegionAvail();

			const char *currentItemProjection = camera.IsOrthographic() ? "Orthographic" : "Perspective";

			ImGui::SetNextItemWidth(region.x * 0.7f);
			if (ImGui::BeginCombo("##Camera Projection", currentItemProjection))
			{
				if (ImGui::Selectable("Orthographic"))
					camera.SetOrthographic();

				if (ImGui::Selectable("Perspective"))
					camera.SetPerspective();

				ImGui::EndCombo();
			}

			ImGui::SameLine();
			ImGui::Checkbox("Primary", &cc.primary);

			ImGui::Separator();

			if (camera.IsOrthographic())
			{
				float zoom = camera.GetZoom();

				ImGui::Text("Zoom");
				ImGui::SameLine(100);
				ImGui::SetNextItemWidth(region.x - 100.0f);
				if (ImGui::DragFloat("##Zoom", &zoom, 0.1f, 0.0f, 100.0f))
					camera.SetZoom(zoom);
			}
			if (camera.IsPerspective())
			{
				float FOV = camera.GetZoom();

				ImGui::Text("Zoom");
				ImGui::SameLine(100);
				ImGui::SetNextItemWidth(region.x - 100.0f);
				if (ImGui::DragFloat("##FOV", &FOV, 0.1f, 0.0f, 90.0f))
					camera.SetFOV(FOV);
			}

			ImGui::Separator();

			float nearClip = camera.GetNearClip();
			float farClip = camera.GetFarClip();

			ImGui::Text("Near Clip");
			ImGui::SameLine(100);
			ImGui::SetNextItemWidth(region.x - 100.0f);
			if (ImGui::DragFloat("##Near Clip", &nearClip, 0.1f, 0.0f, 1000.0f))
				camera.SetNearClip(nearClip);

			ImGui::Text("Far Clip");
			ImGui::SameLine(100);
			ImGui::SetNextItemWidth(region.x - 100.0f);
			if (ImGui::DragFloat("##Far Clip", &farClip, 0.1f, 0.0f, 1000.0f))
				camera.SetFarClip(farClip);
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
	void Inspector::DrawComponentInfo<NativeScriptComponent>()
	{
		Entity entity = m_SelectedEntity;
		auto &nsc = entity.Get<NativeScriptComponent>();

		if (ImGui::CollapsingHeader("Native Script Component"))
		{
			if(nsc.instance != nullptr)
				nsc.OnGui();
		}
	}

	template<>
	void Inspector::DrawComponentInfo<MeshComponent>()
	{
		Entity entity = m_SelectedEntity;
		if (!entity.Has<MeshComponent>())
			return;
		auto &mc = entity.Get<MeshComponent>();

		if (ImGui::CollapsingHeader("Mesh Component"))
		{
			ImGui::TextWrapped("Filepath: %s", mc.filepath.c_str());
			if (ImGui::Button("Load"))
			{
				mc.filepath = Filesystem::OpenFileDialog("");
				mc.Load();
			}

			if (mc.mesh->IsLoaded())
			{
				auto &material = mc.mesh->GetMaterial();
				bool noFill = material->GetFlag(MaterialFlag::NoFill);
				if (ImGui::Checkbox("No Fill", &noFill))
					material->SetFlag(MaterialFlag::NoFill, noFill);
			}

			static bool showMaterials = false;
			if (ImGui::Button("Open Material Settings"))
				showMaterials = true;

			if (showMaterials && !mc.mesh->GetSubMeshes().empty())
			{
				auto &subMaterials = mc.mesh->GetMaterial()->GetSubMaterials();

				ImGui::Begin("Materials", &showMaterials, ImGuiWindowFlags_NoDocking);

				static U32 selected = 0;

				ImGui::BeginChild("left pane", ImVec2(150, 0), true);
				for (int i = 0; i < subMaterials.size(); i++)
				{
					std::string name = subMaterials[i].GetName();
					if (ImGui::Selectable(name.c_str(), i == selected))
						selected = i;
				}
				ImGui::EndChild();
				ImGui::SameLine();

				// If the Mesh changed make sure we don't go out of bounds
				selected = selected >= subMaterials.size() ? 0 : selected;

				ImGui::BeginChild("Settings");
				if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
				{
					if (ImGui::BeginTabItem("Parameters"))
					{
						auto &params = subMaterials[selected].GetPBRMaterialParameters();
						ImGui::ColorEdit3("Albedo Color", &params.albedoColor[0]);
						ImGui::SliderFloat("Metalness", &params.metalness, 0.0f, 1.0f);
						ImGui::SliderFloat("Roughness", &params.roughness, 0.0f, 1.0f);
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Textures"))
					{
						auto &textures = subMaterials[selected].GetPBRMaterialTextures();
						auto &whiteTexture = Renderer::GetEmptyTexture();

						auto CheckForClickAndSetTexture = [](SharedPtr<Texture2D> &texture)
						{
							if (ImGui::IsItemClicked())
							{
								std::string filepath = Filesystem::OpenFileDialog("");
								if (filepath != "")
									texture = Texture2D::Create(filepath);
							}
						};

						// Albedo
						{
							ImGui::Text("Albedo Texture");
							if (!textures.albedoTexture->IsLoaded())
								ImGui::Image(whiteTexture->GetHandle(), ImVec2(64.0f, 64.0f));
							else
								ImGui::Image(textures.albedoTexture->GetHandle(), ImVec2(64.0f, 64.0f));

							CheckForClickAndSetTexture(textures.albedoTexture);
							ImGui::Checkbox("Enable##Albedo", &textures.useAlbedoTexture);
						}

						// Normal Map
						{
							ImGui::Text("Normal Map");
							if (!textures.normalMapTexture->IsLoaded())
								ImGui::Image(whiteTexture->GetHandle(), ImVec2(64.0f, 64.0f));
							else
								ImGui::Image(textures.normalMapTexture->GetHandle(), ImVec2(64.0f, 64.0f));

							CheckForClickAndSetTexture(textures.normalMapTexture);
							ImGui::Checkbox("Enable##Normal", &textures.useNormalMapTexture);
						}

						// Metalness
						{
							ImGui::Text("Metalness Texture");
							if (!textures.metalnessTexture->IsLoaded())
								ImGui::Image(whiteTexture->GetHandle(), ImVec2(64.0f, 64.0f));
							else
								ImGui::Image(textures.metalnessTexture->GetHandle(), ImVec2(64.0f, 64.0f));

							CheckForClickAndSetTexture(textures.metalnessTexture);
							ImGui::Checkbox("Enable##Metalness", &textures.useMetalnessTexture);
						}

						// Roughness
						{
							ImGui::Text("Roughness Texture");
							if (!textures.roughnessTexture->IsLoaded())
								ImGui::Image(whiteTexture->GetHandle(), ImVec2(64.0f, 64.0f));
							else
								ImGui::Image(textures.roughnessTexture->GetHandle(), ImVec2(64.0f, 64.0f));

							CheckForClickAndSetTexture(textures.roughnessTexture);
							ImGui::Checkbox("Enable##Roughness", &textures.useRoughnessTexture);
						}

						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}
				ImGui::EndChild();
				ImGui::End();
			}
		}
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
}