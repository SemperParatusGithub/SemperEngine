#pragma once

#include "SemperEngine/Scene/Entity.h"
#include "SemperEngine/Scene/Components.h"


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
		template<typename Component>
		void DrawComponentInfo(Entity entity);

	private:
		Scene *m_SceneHandle;
	};
}