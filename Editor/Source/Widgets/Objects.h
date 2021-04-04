#pragma once
#include "Widget.h"


enum class Object
{
	Cube = 0
};

namespace Widget
{
	class Objects : public IWidget
	{
	public:
		Objects();
		~Objects();

		virtual void Open() override;
		virtual void Close() override;

		virtual ConstRef<std::string> GetName() const override;

		virtual bool IsOpen() const override;

		virtual void OnRender() override;

	private:
		void DrawObject(const char *label, Object &obj);

	private:
		bool m_IsOpen = true;
		std::string m_Name = "Objects";
	};
}