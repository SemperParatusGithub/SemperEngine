#pragma once

#include "SemperEngine.h"


class TestLayer : public SemperEngine::Layer
{
public:
    TestLayer();
    virtual ~TestLayer() override = default;

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

    SemperEngine::Texture2D *m_SpriteSheet;

    struct SpriteObject
    {
        std::string name;
        SemperEngine::Sprite sprite;
        float posX = 0.0f, posY = 0.0f;
        int indexX = 0, indexY = 0;
    };
    std::vector<SpriteObject> m_Sprites;
};