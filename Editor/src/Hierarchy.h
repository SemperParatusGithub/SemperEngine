#pragma once

#include "SemperEngine/Scene/Scene.h"
#include "SemperEngine/Scene/Entity.h"


namespace SemperEngine
{
	class Hierarchy
	{
	public:
		Hierarchy(Scene *handle);
		~Hierarchy() = default;

		void OnImGui();

		Entity GetSelectedEntity() const { return m_SelectedEntity; }
		void SetSelectedEntiy(Entity entity) { m_SelectedEntity = entity; }

	private:
		Entity m_SelectedEntity;
		Scene *m_SceneHandle;
	};
}