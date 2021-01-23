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
	bool m_SceneViewPortFocused, m_SceneViewPortHovered;
	Vec2i m_ViewportSize;

private:
	SharedPtr<Framebuffer> m_Framebuffer;
	SharedPtr<LogConsole> m_LogConsole;
	SharedPtr<Scene> m_Scene;

	SharedPtr<Hierarchy> m_Hierarchy;
	SharedPtr<Inspector> m_Inspector;

	OrthographicCameraController m_CameraController;
	SharedPtr<Texture2D> m_TestTexture;
};