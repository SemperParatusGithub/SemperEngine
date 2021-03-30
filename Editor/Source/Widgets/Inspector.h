#pragma once
#include "Widget.h"


namespace Widget
{
	class Inspector : public IWidget
	{
	public:
		Inspector();
		~Inspector();

		virtual void Open() override;
		virtual void Close() override;

		virtual ConstRef<std::string> GetName() const override;

		virtual bool IsOpen() const override;

		virtual void OnRender() override;

		void SetSelectedEntity(Entity entity);
		Entity GetSelectedEntity();

	private:
		void DrawComponents();

		template<typename Component>
		void DrawComponentInfo();

		bool DrawSliderFloat3(ConstRef<std::string> name, float labelWidth, Vec3 &vector, float resetValue);

	private:
		bool m_IsOpen = true;
		std::string m_Name = "Inspector";

		Entity m_SelectedEntity;
	};
}