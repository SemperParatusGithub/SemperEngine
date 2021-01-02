#include "Precompiled.h"
#include "EngineApplication.h"
#include "SemperEngine/Log/Log.h"

#include "SemperEngine/Events/EventDispatcher.h"
#include "SemperEngine/Graphics/Renderers/Renderer.h"

// TEMP
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace SemperEngine
{
	EngineApplication *EngineApplication::s_Instance = nullptr;

	EngineApplication::EngineApplication(const std::string &name)
	{
		if (s_Instance)
			throw std::runtime_error("Application already exists");
		s_Instance = this;
		m_Running = true;

		m_Window = Window::Create(1280, 720, name);
		m_Window->SetInterval(1);
		m_Window->SetEventCallbackFunction(SE_BIND_EVENT_FN(EngineApplication::OnEvent));

		m_Backend = Backend::Create();
		Renderer::Init(m_Backend);

		m_ImGuiLayer = new (std::nothrow) ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	EngineApplication::~EngineApplication()
	{
		delete m_Window;
	}

	void EngineApplication::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
			float deltaTime = static_cast<float>(glfwGetTime()) - m_Lastframe;
			m_Lastframe = static_cast<float>(glfwGetTime());

			for (auto *layer : m_LayerStack)
				layer->OnUpdate(deltaTime);

			m_ImGuiLayer->Begin();
			for (auto *layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
		}
	}

	void EngineApplication::Close()
	{
		m_Running = false;
	}

	void EngineApplication::OnEvent(Event &e)
	{
		// SE_CORE_INFO("Event occured: %s", e.ToString().c_str());
		m_ImGuiLayer->OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SE_BIND_EVENT_FN(EngineApplication::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(SE_BIND_EVENT_FN(EngineApplication::OnWindowResize));

		for (const auto &layer : m_LayerStack)
		{
			if (e.Handled)
				break;
			layer->OnEvent(e);
		}
	}

	void EngineApplication::PushLayer(Layer *layer)
	{
		SE_CLIENT_INFO("Pushed Layer: %s", layer->GetName().c_str());

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void EngineApplication::PushOverlay(Layer *layer)
	{
		SE_CLIENT_INFO("Pushed Overlay: %s", layer->GetName().c_str());

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void EngineApplication::BlockImGuiEvents(bool block)
	{
		m_ImGuiLayer->BlockEvents(block);
	}

	Window &EngineApplication::GetWindow()
	{
		return *m_Window;
	}

	EngineApplication &EngineApplication::Instance()
	{
		return *s_Instance;
	}

	bool EngineApplication::OnWindowClose(WindowCloseEvent &e)
	{
		m_Running = false;
		return true;
	}

	bool EngineApplication::OnWindowResize(WindowResizeEvent &e)
	{
		Renderer::SetViewport(0.0f, 0.0f, e.GetWidth(), e.GetHeight());

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		return false;
	}
}
