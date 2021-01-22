#pragma once

#include "SemperEngine/Core/LayerStack.h"

#define OPEN_SANS_REGULAR	0
#define OPEN_SANS_BOLD		1


class ImFont;

namespace SemperEngine
{
	class ImGuiLayer : public Layer
	{
	public:
		static ImFont *GetFont(std::size_t index);

	public:
		ImGuiLayer() : Layer("ImGuiLayer") {}

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event &e) override;

		void Begin();
		void End();

		void BlockEvents(bool block);

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}