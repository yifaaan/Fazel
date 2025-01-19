#pragma once

#include "Core.h"
#include "Window.h"

#include "Fazel/Events/Event.h"
#include "Fazel/Events/ApplicationEvent.h"

namespace Fazel
{
	class FAZEL_API Application
	{
	public:
		Application();

		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> window;
		bool running = true;
	};

	// To be defined in client
	Application* CreateApplication();
}

