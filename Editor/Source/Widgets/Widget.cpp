#include "Widget.h"
#include "Hierarchy.h"
#include "Inspector.h"
#include "Objects.h"


namespace Widget
{
    Manager::Manager(SharedPtr<Scene> scene) : 
        m_Scene(scene)
    {
        SE_ASSERT(scene);
    }
    Manager::~Manager()
    {
    }

    void Manager::SetSelectedEntity(Entity entity)
    {
        m_SelectedEntity = entity;

        // Apply selection for all widgets
        GetWidget<Hierarchy>()->SetSelectedEntity(entity);
        GetWidget<Inspector>()->SetSelectedEntity(entity);
    }
    Entity Manager::GetSelectedEntity()
    {
        return m_SelectedEntity;
    }

    void Manager::OnImGui()
    {
        m_SelectedEntity = GetWidget<Hierarchy>()->GetSelectedEntity();
        GetWidget<Hierarchy>()->SetScene(m_Scene);
        GetWidget<Inspector>()->SetSelectedEntity(m_SelectedEntity);

        for (auto widget : m_Widgets)
            widget.second->OnRender();
    }
}