#include "Precompiled.h"
#include "Scene.h"

#include <imgui.h>

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
				float tra[3] = { translation.x,translation.y,translation.z, };
				float rot[3] = { rotation.x,rotation.y,rotation.z, };
				float sca[3] = { scale.x,scale.y,scale.z, };

				ImGui::PushID((uint64_t)UUID);
				if (ImGui::DragFloat3("Translation", tra))
					transform.SetTranslation(Vec3 { tra[0], tra[1], tra[2] });
				if (ImGui::DragFloat3("Rotation", rot))
					transform.SetRotation(Vec3 { rot[0], rot[1], rot[2] });
				if (ImGui::DragFloat3("Scale", sca))
					transform.SetScale(Vec3 { sca[0], sca[1], sca[2] });
				ImGui::PopID();

				// ImGui::Text("Translation: %.2f, %.2f, %.2f", translation.x, translation.y, translation.z);
				// ImGui::Text("Rotation: %.2f, %.2f, %.2f", rotation.x, rotation.y, rotation.z);
				// ImGui::Text("Scale: %.2f, %.2f, %.2f", scale.x, scale.y, scale.z);
			}
		}
	}
}