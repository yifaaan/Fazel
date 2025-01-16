#include "fzpch.h"
#include "WindowsWindow.h"

namespace Fazel
{
	static bool s_GLFWInitialized = false;

	auto Window::Create(const WindowProps& props) -> Window*
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	auto WindowsWindow::Init(const WindowProps& props) -> void
	{
		data.title = props.title;
		data.width = props.width;
		data.height = props.height;

		FZ_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			FZ_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		window = glfwCreateWindow((int)props.width, (int)props.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);
	}

	auto WindowsWindow::Shutdown() -> void
	{
		glfwDestroyWindow(window);
	}

	auto WindowsWindow::OnUpdate() -> void
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	auto WindowsWindow::SetVSync(bool enabled) -> void
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		data.vSync = enabled;
	}

	auto WindowsWindow::IsVSync() const -> bool
	{
		return data.vSync;
	}
}