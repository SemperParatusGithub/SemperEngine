#include "pch.h"
#include "LayerStack.h"

namespace SemperEngine
{

    LayerStack::LayerStack() : 
        m_LayerInsertIndex(0)
    {
    }

    LayerStack::~LayerStack()
    {
        for (Layer *layer : m_LayerStack)
        {
            layer->OnDetach();
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer *layer)
    {
        m_LayerStack.emplace(m_LayerStack.begin() + m_LayerInsertIndex, layer);
        m_LayerInsertIndex++;
    }

    void LayerStack::PushOverlay(Layer *overlay)
    {
        m_LayerStack.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer *layer)
    {
        auto it = std::find(m_LayerStack.begin(), m_LayerStack.begin() + m_LayerInsertIndex, layer);
        if (it != m_LayerStack.begin() + m_LayerInsertIndex)
        {
            layer->OnDetach();
            m_LayerStack.erase(it);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer *overlay)
    {
        auto it = std::find(m_LayerStack.begin() + m_LayerInsertIndex, m_LayerStack.end(), overlay);
        if (it != m_LayerStack.end())
        {
            overlay->OnDetach();
            m_LayerStack.erase(it);
        }
    }

    LayerStackIterator LayerStack::begin()
    {
        return m_LayerStack.begin();
    }

    LayerStackIterator LayerStack::end()
    {
        return m_LayerStack.end();
    }

    LayerStackConstIterator LayerStack::begin() const
    {
        return m_LayerStack.begin();
    }

    LayerStackConstIterator LayerStack::end() const
    {
        return m_LayerStack.end();
    }

    LayerStackReverseIterator LayerStack::rbegin()
    {
        return m_LayerStack.rbegin();
    }

    LayerStackReverseIterator LayerStack::rend()
    {
        return m_LayerStack.rend();
    }

    LayerStackConstReverseIterator LayerStack::rbegin() const
    {
        return m_LayerStack.rbegin();
    }

    LayerStackConstReverseIterator LayerStack::rend() const
    {
        return m_LayerStack.rend();
    }

}