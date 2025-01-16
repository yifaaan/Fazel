#pragma once

#include "Core.h"
#include "Fazel/Events/Event.h"
#include "Window.h"

namespace Fazel
{
	class FAZEL_API Application
	{
	public:
		Application();

		virtual ~Application() = default;

		void Run();

	private:
		std::unique_ptr<Window> window;
		bool running = true;
	};

	// To be defined in client
	Application* CreateApplication();
}

