#include "fzpch.h"
#include "Application.h"

#include "Fazel/Events/ApplicationEvent.h"
#include "Fazel/Log.h"
#include "Fazel/Events/Event.h"


#include <GLFW/glfw3.h>

namespace Fazel
{

	Application::Application()
	{
		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	void Application::Run()
	{
		//WindowResizeEvent e(1280, 720);
		//if (e.IsInCategory(EventCategoryApplication))
		//{
		//	FZ_TRACE(e);
		//}
		//if (e.IsInCategory(EventCategoryInput))
		//{
		//	FZ_TRACE(e);
		//}

		while (running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClosed, this, std::placeholders::_1));
		FZ_CORE_TRACE("{}", e);
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		running = false;
		return true;
	}
}