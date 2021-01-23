#pragma once

#include "SemperEngine/Scene/Entity.h"


namespace SemperEngine
{
	class Inspector
	{
	public:
		Inspector(Scene *handle);
		~Inspector() = default;

		void OnImGui(Entity selectedEntity);

		bool DrawSliderFloat3(ConstRef<std::string> name, float labelWidth, Vec3 &vector, float resetValue);

	private:
		bool DrawEntity(Entity entity);		// Returns true if Entity was removed

	private:
		Scene *m_SceneHandle;
	};
}