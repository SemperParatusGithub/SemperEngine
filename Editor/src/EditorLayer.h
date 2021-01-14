#pragma once
#include "SemperEngine.h"


class EditorLayer : public SemperEngine::Layer
{
public:
	EditorLayer();
	virtual ~EditorLayer() override = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(SemperEngine::Event &e) override;

private:
	bool m_SceneViewPortFocused, m_SceneViewPortHovered;

private:
	SemperEngine::Framebuffer *m_Framebuffer;
	SemperEngine::OrthographicCameraController m_CameraController;
	SemperEngine::Texture2D *m_TestTexture;

	SemperEngine::SharedPtr<SemperEngine::LogConsole> m_LogConsole;
	SemperEngine::SharedPtr<SemperEngine::Scene> m_Scene;

	SemperEngine::Entity m_TestEntity;
};