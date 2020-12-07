#pragma once
#include "SemperEngine/Core/Window.h"

#include "SemperEngine/ImGui/ImGuiLayer.h"

#include "SemperEngine/Events/MouseEvent.h"
#include "SemperEngine/Events/keyEvent.h"
#include "SemperEngine/Events/ApplicationEvent.h"

#include "SemperEngine/Renderer/Backend.h"

namespace SemperEngine
{

	class EngineApplication
	{
	public:
		EngineApplication(const std::string &name);
		virtual ~EngineApplication();

		void Run();
		void Close();

		void OnEvent(Event &e);

		void PushLayer(Layer *layer);
		void PushOverlay(Layer *layer);

		Window &GetWindow();

		static EngineApplication &Instance();

		bool OnWindowClose(WindowCloseEvent &e);
		bool OnWindowResize(WindowResizeEvent &e);
		
	private:
		bool m_Running = false;
		bool m_Minimized = false;
		float m_Lastframe = 0.0f;

		Window *m_Window;
		Backend *m_Backend;
		LayerStack m_LayerStack;
		ImGuiLayer *m_ImGuiLayer;

	protected:
		static EngineApplication *s_Instance;

		unsigned int shaderProgram, vao;
	};
	
}