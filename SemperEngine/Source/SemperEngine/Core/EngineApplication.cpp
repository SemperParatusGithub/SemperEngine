#include "Precompiled.h"
#include "EngineApplication.h"
#include "SemperEngine/Log/Log.h"

#include "SemperEngine/Events/EventDispatcher.h"
#include "SemperEngine/Graphics/Renderers/Renderer.h"

#include <GLFW/glfw3.h>		// TODO: Remove
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <Windows.h>		// TODO: Remove


namespace SemperEngine
{
	EngineApplication *EngineApplication::s_Instance = nullptr;

	EngineApplication::EngineApplication(ConstRef<std::string> name)
	{
		if (s_Instance)
			SE_ASSERT_MSG(false, "Application already exists!");
		s_Instance = this;
		m_Running = true;

		m_Window.reset(Window::Create(1280, 720, name));
		m_Window->SetInterval(1);
		m_Window->SetEventCallbackFunction(SE_BIND_EVENT_FN(EngineApplication::OnEvent));

		m_Backend.reset(Backend::Create());
		Renderer::Init(m_Backend.get());

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	EngineApplication::~EngineApplication()
	{
	}

	void EngineApplication::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
			m_DeltaTime = static_cast<float>(glfwGetTime()) - m_LastFrame;
			m_LastFrame = static_cast<float>(glfwGetTime());

			for (auto *layer : m_LayerStack)
				layer->OnUpdate(m_DeltaTime);

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
		// SE_CORE_INFO("Event occurred: %s", e.ToString().c_str());
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

	float EngineApplication::GetFrametime()
	{
		return m_DeltaTime * 1000.0f;
	}
	float EngineApplication::GetFramerate()
	{
		return 1.0f / m_DeltaTime;
	}
	std::string EngineApplication::OpenFile(const char *filter)
	{
		OPENFILENAMEA ofn;				// common dialog box structure
		CHAR szFile[260] = { 0 };       // if using TCHAR macros

		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow *) m_Window->GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn) == TRUE)
		{
			return ofn.lpstrFile;
		}
		return std::string();
	}
}