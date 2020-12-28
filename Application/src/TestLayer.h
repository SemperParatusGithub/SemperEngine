#pragma once

#include "SemperEngine.h"


class TestLayer : public SemperEngine::Layer
{
public:
    TestLayer();
    ~TestLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(SemperEngine::Event & e) override;

private:
    SemperEngine::OrthographicCameraController m_CameraController;
    SemperEngine::Texture2D *m_GridTexture;
    SemperEngine::Texture2D *m_StoneTexture;
    SemperEngine::Texture2D *m_BrickTexture;
};