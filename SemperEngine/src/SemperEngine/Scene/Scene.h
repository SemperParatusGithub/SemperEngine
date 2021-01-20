#pragma once
#include "SemperEngine/Core/Types.h"

#include "ECS/ECS.h"
#include "Components.h"


namespace SemperEngine
{
	class Entity;

	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity();
		void RemoveEntity(Entity entity);

		ECS::World GetWorld();

		void OnImGuiRender();

	private:
		void DrawInspectorComponentInfo(Entity entity);
		static bool DrawSliderFloat3(ConstRef<std::string> label, float labelWidth, Vec3 &vector, float resetValue);

	private:
		friend class Entity;

	private:
		ECS::World m_World;
		ECS::EntityHandle m_ActiveEntityHandle = ECS::NullEntity;
	};
}