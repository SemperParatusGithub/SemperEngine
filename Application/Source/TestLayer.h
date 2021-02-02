#pragma once
#include "SemperEngine.h"

#if 0


using namespace SemperEngine;


class TestLayer : public Layer
{
public:
    TestLayer();
    virtual ~TestLayer() override = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnUpdate(float deltaTime) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Event &e) override;

private:
    OrthographicCameraController m_CameraController;
    SharedPtr<Texture2D> m_GridTexture;
    SharedPtr<Texture2D> m_StoneTexture;
    SharedPtr<Texture2D> m_BrickTexture;

    SharedPtr<Texture2D> m_SpriteSheet;

    std::vector<std::pair<std::string, Sprite>> m_Sprites;
};
#endif