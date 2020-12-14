#include "SemperEngine.h"

class ApplicationLayer : public SemperEngine::Layer
{
public:
    ApplicationLayer();
	~ApplicationLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(SemperEngine::Event &e) override;

private:
    float m_Color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

    SemperEngine::VertexArray *m_VertexArray;
    SemperEngine::VertexBuffer *m_VertexBuffer;
    SemperEngine::IndexBuffer *m_IndexBuffer;
    SemperEngine::Texture2D *m_BackgroundTexture;

    SemperEngine::Shader *m_Shader;
};