#pragma once
#include "SemperEngine.h"

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
};