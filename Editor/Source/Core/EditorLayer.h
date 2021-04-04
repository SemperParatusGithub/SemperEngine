#pragma once
#include <SemperEngine.h>

#include "Widgets/Widget.h"

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
	void BeginDockspace();
	void EndDockspace();

	void UpdateGizmos();
	
	void OpenScene();
	void SaveSceneAs();

	void UpdateWindowTitle();

private:
	bool m_SceneViewportFocused, m_SceneViewportHovered;
	bool m_ViewportSizeChanged;
	Vec2f m_ViewportPosition;
	Vec2f m_ViewportSize;

private:
	SharedPtr<Scene> m_Scene;

	SharedPtr<Texture2D> m_PlayButtonTexture;
	SharedPtr<Texture2D> m_PauseButtonTexture;
	SharedPtr<Texture2D> m_ExitButtonTexture;

	UniquePtr<Widget::Manager> m_WidgetManager;

	EditorCamera m_EditorCamera;

	int m_ImGuizmoOperation = -1;
};