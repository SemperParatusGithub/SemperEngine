#pragma once
#include "SemperEngine/Core/Window.h"

#include "SemperEngine/Graphics/ImGui/ImGuiLayer.h"

#include "SemperEngine/Events/MouseEvent.h"
#include "SemperEngine/Events/keyEvent.h"
#include "SemperEngine/Events/ApplicationEvent.h"

#include "SemperEngine/Graphics/Backend/API/Backend.h"


namespace SemperEngine
{
	class EngineApplication
	{
	public:
		EngineApplication(ConstRef<std::string> name);
		virtual ~EngineApplication();

		void Run();
		void Close();

		void OnEvent(Event &e);

		void PushLayer(Layer *layer);
		void PushOverlay(Layer *layer);

		void BlockImGuiEvents(bool block);

		Window &GetWindow();

		static EngineApplication &Instance();

		bool OnWindowClose(WindowCloseEvent &e);
		bool OnWindowResize(WindowResizeEvent &e);

		float GetFrametime();	// ms
		float GetFramerate();	
		
	private:
		bool m_Running = false;
		bool m_Minimized = false;
		float m_LastFrame = 0.0f;
		float m_DeltaTime = 0.0f;

		SharedPtr<Window> m_Window;
		SharedPtr<Backend> m_Backend;
		LayerStack m_LayerStack;
		ImGuiLayer *m_ImGuiLayer;

	protected:
		static EngineApplication *s_Instance;

		unsigned int shaderProgram, vao;
	};
}