#pragma once
#include "SemperEngine/Events/Event.h"
#include "Defines.h"


namespace SemperEngine
{
    class Layer
    {
    public:
        Layer(const std::string &name = "Layer")
            : m_Name(name)
        {
        }
        virtual ~Layer() = default;

        virtual void OnAttach()
        {
        }
        virtual void OnDetach()
        {
        }
        virtual void OnUpdate(float deltaTime)
        {
        }
        virtual void OnImGuiRender()
        {
        }
        virtual void OnEvent(Event &e)
        {
        }

        inline std::string GetName() const { return m_Name; }

    protected:
        std::string m_Name;
    };
}