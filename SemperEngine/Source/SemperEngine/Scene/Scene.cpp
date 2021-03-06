#include "Precompiled.h"
#include "Scene.h"

#include <cereal/cereal.hpp>
#include <cereal/archives/xml.hpp>

#include "Entity.h"
#include "Components.h"

#include "SemperEngine/Graphics/Renderers/Renderer.h"
#include "SemperEngine/Graphics/Renderers/Batcher2D.h"
#include "SemperEngine/Util/Timer.h"

#include "SemperEngine/Graphics/Renderers/SceneRenderer.h"


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

	void Scene::OnUpdate(float deltaTime, ConstRef<EditorCamera> camera)
	{
		Mat4 projectionViewMatrix = camera.GetProjectionView();

		switch (m_SceneState)
		{
			case SceneState::Editing:
			{
				SceneInfo sceneInfo;
				sceneInfo.context = this;
				sceneInfo.cameraInfo.projectionViewMatrix = camera.GetProjectionView();
				sceneInfo.cameraInfo.cameraPosition = camera.GetPosition();

				SceneRenderer::BeginScene(sceneInfo);

				auto view = m_Registry.view<const TransformComponent, const MeshComponent>();
				view.each([=](const auto ent, const TransformComponent &tc, const MeshComponent &mc)
					{
						SceneRenderer::SubmitMesh(mc.mesh, tc.transform);
					});

				SceneRenderer::EndScene();

			} break;

			case SceneState::Pausing:
			{
				// Don't update Scripts while pausing!
				// Get primary camera entity and override scene camera with it
				// Render
			} break;

			case SceneState::Playing:
			{
				// Update NativeScriptComponents
				// Get primary camera entity and override scene camera with it
				// Render
			} break;
		}
	}

	void Scene::OnResize(U32 viewportWidth, U32 viewportHeight)
	{
		SceneRenderer::OnResize(viewportWidth, viewportHeight);
	}

	void Scene::Play()
	{
		m_SceneState = SceneState::Playing;

		// Create all native scripts
		auto view = m_Registry.view<NativeScriptComponent>();
		for (const auto ent : view)
		{
			auto entity = Entity(ent, this);
			auto &nsc = entity.Get<NativeScriptComponent>();
			nsc.instance = nsc.CreateInstance();
			nsc.instance->m_Entity = entity;
			nsc.OnCreate();
		}
	}
	void Scene::Pause()
	{
		if (m_SceneState != SceneState::Editing)
		{
			if (m_SceneState == SceneState::Pausing)
				m_SceneState = SceneState::Playing;
			else
				m_SceneState = SceneState::Pausing;
		}
	}
	void Scene::ReturnToEditing()
	{
		if (m_SceneState != SceneState::Editing)
		{
			m_SceneState = SceneState::Editing;

			// Destroy all native scripts
			auto view = m_Registry.view<NativeScriptComponent>();
			for (const auto ent : view)
			{
				auto entity = Entity(ent, this);
				auto &nsc = entity.Get<NativeScriptComponent>();
				nsc.OnDestroy();
				nsc.DestroyInstance(&nsc);
			}
		}
	}

	void Scene::Serialize(ConstRef<std::string> filepath)
	{
		SE_CORE_INFO("Serializing Scene: %s", filepath.c_str());

		Util::Timer timer;
		timer.Start();

		std::ofstream ofStream(filepath);
		UniquePtr<cereal::XMLOutputArchive> archive = MakeUnique<cereal::XMLOutputArchive>(ofStream);

		// Serialize general scene info
		archive->operator()( cereal::make_nvp("General", *this) );

		// Serialize all entities of the scene
		entt::snapshot { m_Registry }.entities(*archive).component<ALL_COMPONENTS>(*archive);
	
		auto elapsed = timer.GetTime().time;
		SE_CORE_INFO("Saving the Scene took: %.2f ms", elapsed);
	} 

	void Scene::Deserialize(ConstRef<std::string> filepath)
	{
		SE_CORE_INFO("Deserializing Scene: %s", filepath.c_str());

		Util::Timer timer;
		timer.Start();

		std::ifstream ifStream(filepath);
		UniquePtr<cereal::XMLInputArchive> archive = MakeUnique<cereal::XMLInputArchive>(ifStream);
	
		// Load general Scene info
		archive->operator()( cereal::make_nvp("General", *this) );

		// Load all entities
		m_Registry.clear();
		entt::snapshot_loader { m_Registry }.entities(*archive).component<ALL_COMPONENTS>(*archive);
	
		auto elapsed = timer.GetTime().time;
		SE_CORE_INFO("Loading the Scene took: %.2f ms", elapsed);
	}
}