#pragma once

#include "Core.h"

namespace Fazel
{
	class FAZEL_API Application
	{
	public:
		Application() = default;

		virtual ~Application() = default;

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}

