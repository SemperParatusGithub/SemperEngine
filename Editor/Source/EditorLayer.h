#pragma once
#include "SemperEngine.h"

#include "Inspector.h"
#include "Hierarchy.h"


using namespace SemperEngine;


class EditorLayer : public Layer
{
public:
	EditorLayer();
	virtual ~EditorLayer() override = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Event &e) override;

private:
	void OpenScene();
	void SaveSceneAs();

	void UpdateWindowTitle();

private:
	bool m_SceneViewPortFocused, m_SceneViewPortHovered;
	Vec2f m_ViewportPosition;
	Vec2f m_ViewportSize;

private:
	SharedPtr<Scene> m_Scene;
	SharedPtr<Hierarchy> m_Hierarchy;
	SharedPtr<Inspector> m_Inspector;

	SharedPtr<Texture2D> m_PlayButtonTexture;
	SharedPtr<Texture2D> m_PauseButtonTexture;
	SharedPtr<Texture2D> m_ExitButtonTexture;

	EditorCamera m_EditorCamera;

	int m_ImGuizmoOperation = -1;
};