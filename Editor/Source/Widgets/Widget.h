#pragma once
#include <SemperEngine.h>

using namespace SemperEngine;


namespace Widget
{
	class IWidget
	{
	public:
		virtual void Open() = 0;
		virtual void Close() = 0;

		virtual ConstRef<std::string> GetName() const = 0;

		virtual bool IsOpen() const = 0;

		virtual void OnRender() = 0;
	};

	class Manager
	{
	public:
		Manager(SharedPtr<Scene> scene);
		~Manager();

		template<typename WidgetType>
		SharedPtr<WidgetType> GetWidget()
		{
			if (m_Widgets.find(std::type_index(typeid(WidgetType))) != m_Widgets.end())
			{
				SharedPtr<IWidget> widget = m_Widgets[std::type_index(typeid(WidgetType))];
				return reinterpret_cast<SharedPtr<WidgetType>&>(widget);
			}
			SE_ASSERT(false);
		}

		void SetSelectedEntity(Entity entity);
		Entity GetSelectedEntity();

		void OnImGui();

		template<typename WidgetType, typename ... Args>
		void AddWidget(Args && ... args)
		{
			auto index = std::type_index(typeid(WidgetType));

			m_Widgets[index] = MakeShared<WidgetType>(std::forward<Args>(args)...);
		}


	private:
		SharedPtr<Scene> m_Scene;
		Entity m_SelectedEntity;
		std::unordered_map<std::type_index, SharedPtr<IWidget>> m_Widgets;
	};
}