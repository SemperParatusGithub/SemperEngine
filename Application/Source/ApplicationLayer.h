#pragma once
#include "SemperEngine.h"

using namespace SemperEngine;


class ApplicationLayer : public Layer
{
public:
    ApplicationLayer();
	~ApplicationLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Event &e) override;

private:
    float m_Color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

    OrthographicCameraController m_CameraController;

    SharedPtr<VertexArray> m_VertexArray;
    SharedPtr<VertexBuffer> m_VertexBuffer;
    SharedPtr<IndexBuffer> m_IndexBuffer;
    SharedPtr<Texture2D> m_Texture;

	SharedPtr<Shader> m_Shader;
    SharedPtr<Shader> m_FlatColorShader;
};