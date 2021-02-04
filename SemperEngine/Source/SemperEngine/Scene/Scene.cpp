#include "Precompiled.h"
#include "Scene.h"

#include "Entity.h"
#include "Components.h"

#include "SemperEngine/Graphics/Renderers/Batcher2D.h"


namespace SemperEngine
{
	Entity Scene::CreateEntity(ConstRef<std::string> name)
	{
		SE_CORE_INFO("Created Entity: %s", name.c_str());

		auto handle = m_Registry.create();
		auto entity = Entity(handle, this);

		// Add default components
		entity.Add<IdentificationComponent>(IdentificationComponent { name, {} });
		entity.Add<TransformComponent>(TransformComponent {});

		return entity;
	}

	Entity Scene::CreateEmptyEntity(ConstRef<std::string> name)
	{
		SE_CORE_INFO("Creating empty entity: %s", name.c_str());

		auto handle = m_Registry.create();
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
			m_Registry.destroy(entity.GetHandle());
		}
		else {
			SE_CORE_WARN("Tried to destroy invalid entity");
		}
	}

	void Scene::OnUpdate(float deltaTime, ConstRef<Mat4> projectionView)
	{
		Batcher2D::BeginScene(projectionView);

		auto view = m_Registry.view<const TransformComponent, const SpriteComponent>();

		view.each([](const auto ent, const TransformComponent &tc, const SpriteComponent &sc)
			{
				Batcher2D::DrawSprite(tc.transform, sc.sprite);
			});

		Batcher2D::EndScene();
	}

	void Scene::OnUpdateEditor(float deltaTime, ConstRef<EditorCamera> camera)
	{
		OnUpdate(deltaTime, camera.GetProjectionView());
	}

	entt::registry &Scene::GetRegistry()
	{
		return m_Registry;
	}
}