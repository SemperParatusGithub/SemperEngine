#pragma once

#include "Layer.h"


namespace SemperEngine
{
    using LayerStackIterator = std::vector<Layer *>::iterator;
    using LayerStackConstIterator = std::vector<Layer *>::const_iterator;
    using LayerStackReverseIterator = std::vector<Layer *>::reverse_iterator;
    using LayerStackConstReverseIterator = std::vector<Layer *>::const_reverse_iterator;

    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);
        void PopLayer(Layer *layer);
        void PopOverlay(Layer *layer);

        LayerStackIterator begin();
        LayerStackIterator end();
        LayerStackConstIterator begin() const;
        LayerStackConstIterator end() const;

        LayerStackReverseIterator rbegin();
        LayerStackReverseIterator rend();
        LayerStackConstReverseIterator rbegin() const;
        LayerStackConstReverseIterator rend() const;

    private:
        std::vector<Layer *> m_LayerStack;
        uint32_t m_LayerInsertIndex;
    };
}