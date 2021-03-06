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
		enum class SceneState
		{
			Editing = 0,
			Playing,
			Pausing
		};

	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(ConstRef<std::string> name = "Entity");
		Entity CreateEmptyEntity(ConstRef<std::string> name = "Empty Entity");

		entt::registry &GetRegistry();

		void OnUpdate(float deltaTime, ConstRef<EditorCamera> camera);
		// Doesn't resize the editor camera
		void OnResize(U32 viewportWidth, U32 viewportHeight);

		void Play();
		void Pause();
		void ReturnToEditing();

		inline bool IsPlaying() const { return m_SceneState == SceneState::Playing; }

		std::string GetName() const { return m_Name; }
		std::string GetVersion() const { return m_Version; }

		void Serialize(ConstRef<std::string> filepath);
		void Deserialize(ConstRef<std::string> filepath);

		template<typename Archive>
		void save(Archive &archive) const
		{
			archive( cereal::make_nvp("Name", m_Name),
					 cereal::make_nvp("Version", m_Version) );
		}
		template<typename Archive>
		void load(Archive &archive)
		{
			archive( cereal::make_nvp("Name", m_Name),
					 cereal::make_nvp("Version", m_Version) );
		}

	private:
		SceneState m_SceneState = SceneState::Editing;

		std::string m_Name = "Unnamed Scene";
		std::string m_Version = "1.1";

		entt::registry m_Registry;
	};
}