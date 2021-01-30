#include "Precompiled.h"
#include "Scene.h"

#include <imgui.h>
#include <imgui_internal.h>
#include "SemperEngine/Graphics/ImGui/ImGuiLayer.h"

#include "Entity.h"
#include "Components.h"

#include "SemperEngine/Graphics/Renderers/Batcher2D.h"

#include "SemperEngine/Core/EngineApplication.h"	// TODO: remove me


namespace SemperEngine
{
	Entity Scene::CreateEntity(ConstRef<std::string> name)
	{
		SE_CORE_INFO("Created Entity: %s", name.c_str());

		auto handle = m_World.CreateEntity();
		auto entity = Entity(handle, this);

		// Add default components
		entity.Add<IdentificationComponent>(IdentificationComponent { name, {} });
		entity.Add<TransformComponent>(TransformComponent {});

		return entity;
	}

	Entity Scene::CreateEmptyEntity(ConstRef<std::string> name)
	{
		SE_CORE_INFO("Creating empty entity: %s", name.c_str());

		auto handle = m_World.CreateEntity();
		auto entity = Entity(handle, this);

		// Every Entity has an ID
		entity.Add<IdentificationComponent>(IdentificationComponent { name, {} });

		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		if(entity)
		{
			SE_CORE_INFO("Destroyed Entity", entity.Get<IdentificationComponent>().name.c_str());
			m_World.DestroyEntity(entity.GetHandle());
		}
		else {
			SE_CORE_WARN("Tried to destroy invalid entity");
		}
	}

	bool Scene::IsValid(Entity entity)
	{
		return m_World.IsValid(entity.GetHandle());
	}

	void Scene::OnUpdate(float deltaTime, ConstRef<Mat4> projectionView)
	{
		Batcher2D::BeginScene(projectionView);

		for (auto entityHandle : m_World)
		{
			Entity currentEntity = Entity(entityHandle, this);

			if (currentEntity.Has<SpriteComponent>() && currentEntity.Has<TransformComponent>())
			{
				auto sprite = currentEntity.Get<SpriteComponent>().sprite;
				auto transform = currentEntity.Get<TransformComponent>().transform;

				Batcher2D::DrawSprite(transform, sprite);
			}
		}

		Batcher2D::EndScene();
	}

	void Scene::OnUpdateEditor(float deltaTime, ConstRef<EditorCamera> camera)
	{
		OnUpdate(deltaTime, camera.GetProjectionView());
	}

	ECS::World &Scene::GetWorld()
	{
		return m_World;
	}
}