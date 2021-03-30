#pragma once
#include "Widget.h"


namespace Widget
{
	class Hierarchy : public IWidget
	{
	public:
		Hierarchy();
		~Hierarchy();

		virtual void Open() override;
		virtual void Close() override;

		virtual ConstRef<std::string> GetName() const override;

		virtual bool IsOpen() const override;

		virtual void OnRender() override;

		void SetScene(SharedPtr<Scene> scene);
		SharedPtr<Scene> GetScene();

		void SetSelectedEntity(Entity entity);
		Entity GetSelectedEntity();

	private:
		bool m_IsOpen = true;
		std::string m_Name = "Hierarchy";

		SharedPtr<Scene> m_Scene;
		Entity m_SelectedEntity;
	};
}