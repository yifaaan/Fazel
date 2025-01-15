#include "Application.h"

#include "Fazel/Events/ApplicationEvent.h"
#include "Fazel/Log.h"
#include "Fazel/Events/Event.h"

namespace Fazel
{
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			FZ_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			FZ_TRACE(e);
		}

		while (true);
	}
}