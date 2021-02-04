#pragma once
#include "SemperEngine/Core/Types.h"

#include "SemperEngine/Graphics/Camera/OrthographicCamera.h"
#include "SemperEngine/Graphics/Camera/EditorCamera.h"

#include <entt.hpp>


namespace SemperEngine
{
	class Entity;

	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(ConstRef<std::string> name = "Entity");
		Entity CreateEmptyEntity(ConstRef<std::string> name = "Empty Entity");
		void DestroyEntity(Entity entity);

		void OnUpdate(float deltaTime, ConstRef<Mat4> projectionView);
		void OnUpdateEditor(float deltaTime, ConstRef<EditorCamera> camera);

		entt::registry &GetRegistry();

	private:
		entt::registry m_Registry;
	};
}