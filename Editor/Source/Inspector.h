#pragma once

#include "SemperEngine/Scene/Entity.h"


namespace SemperEngine
{
	class Inspector
	{
	public:
		Inspector(SharedPtr<Scene> handle);
		~Inspector() = default;

		void OnImGui(Entity selectedEntity);

		static bool DrawSliderFloat3(ConstRef<std::string> name, float labelWidth, Vec3 &vector, float resetValue);

	private:
		template<typename Component>
		void DrawComponentInfo(Entity entity);

	private:
		SharedPtr<Scene> m_SceneHandle;
	};
}