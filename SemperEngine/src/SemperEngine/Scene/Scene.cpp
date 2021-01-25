#include "Precompiled.h"
#include "Scene.h"

#include <imgui.h>
#include <imgui_internal.h>
#include "SemperEngine/Graphics/ImGui/ImGuiLayer.h"

#include "Entity.h"
#include "SemperEngine/Graphics/Renderers/Batcher2D.h"


namespace SemperEngine
{
	Entity Scene::CreateEntity()
	{
		SE_CORE_INFO("Created Entity: Entity");

		auto handle = m_World.CreateEntity();
		auto entity = Entity(handle, this);

		// Add default components
		entity.Add<IdentificationComponent>(IdentificationComponent { "Entity", {} });
		entity.Add<TransformComponent>(TransformComponent {});

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
			SE_CORE_WARN("Tryed to destroy invalid entity");
		}
	}

	bool Scene::IsValid(Entity entity)
	{
		return m_World.IsValid(entity.GetHandle());
	}

	void Scene::OnUpdate(float deltaTime, ConstRef<OrthographicCamera> camera)
	{
		Batcher2D::BeginScene(camera);

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

	ECS::World &Scene::GetWorld()
	{
		return m_World;
	}
}