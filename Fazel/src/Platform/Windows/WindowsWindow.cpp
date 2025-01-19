#include "fzpch.h"
#include "WindowsWindow.h"

#include "Fazel/Events/ApplicationEvent.h"
#include "Fazel/Events/KeyEvent.h"
#include "Fazel/Events/MouseEvent.h"

namespace Fazel
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		FZ_CORE_ERROR("GLFW error （{}}: {}", error, description);
	}

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
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		window = glfwCreateWindow((int)props.width, (int)props.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);

		// set GLFW callbacks
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data.width = width;
			data.height = height;

			WindowResizeEvent event{ static_cast<unsigned int>(width), static_cast<unsigned int>(height) };
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			
			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event{ key, 0 };
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event{ key, 0 };
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event{ key, 1 };
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event{ button };
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event{ button };
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event{ static_cast<float>(xoffset), static_cast<float>(yoffset) };
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent event{ static_cast<float>(xpos), static_cast<float>(ypos) };
			data.EventCallback(event);
		});
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