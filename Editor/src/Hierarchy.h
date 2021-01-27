#pragma once

#include "SemperEngine/Scene/Scene.h"
#include "SemperEngine/Scene/Entity.h"


namespace SemperEngine
{
	class Hierarchy
	{
	public:
		Hierarchy(SharedPtr<Scene> handle);
		~Hierarchy() = default;

		void OnImGui();

		Entity GetSelectedEntity() const { return m_SelectedEntity; }
		void SetSelectedEntiy(Entity entity) { m_SelectedEntity = entity; }

	private:
		Entity m_SelectedEntity;
		SharedPtr<Scene> m_SceneHandle;
	};
}