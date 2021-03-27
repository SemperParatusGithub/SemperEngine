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
};