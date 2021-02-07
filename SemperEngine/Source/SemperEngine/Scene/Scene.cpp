#include "Precompiled.h"
#include "Scene.h"

#include <cereal/cereal.hpp>
#include <cereal/archives/xml.hpp>

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

	entt::registry &Scene::GetRegistry()
	{
		return m_Registry;
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

	void Scene::Serialize(ConstRef<std::string> filepath)
	{
		SE_CORE_INFO("Serializing Scene: %s", filepath.c_str());

		std::ofstream ofStream(filepath);
		UniquePtr<cereal::XMLOutputArchive> archive = MakeUnique<cereal::XMLOutputArchive>(ofStream);

		// Serialize general scene info
		archive->operator()( cereal::make_nvp("General", *this) );

		// Serialize all entities of the scene
		entt::snapshot { m_Registry }.entities(*archive).component<IdentificationComponent, TransformComponent, SpriteComponent>(*archive);
	} 

	void Scene::Deserialize(ConstRef<std::string> filepath)
	{
		SE_CORE_INFO("Deserializing Scene: %s", filepath.c_str());

		std::ifstream ifStream(filepath);
		UniquePtr<cereal::XMLInputArchive> archive = MakeUnique<cereal::XMLInputArchive>(ifStream);
	
		// Load general Scene info
		archive->operator()( cereal::make_nvp("General", *this) );

		// Load all entities
		m_Registry.clear();
		entt::snapshot_loader { m_Registry }.entities(*archive).component<IdentificationComponent, TransformComponent, SpriteComponent>(*archive);
	}
}