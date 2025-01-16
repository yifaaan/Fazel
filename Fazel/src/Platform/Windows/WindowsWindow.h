#pragma once

#include "Fazel/Window.h"

#include <GLFW/glfw3.h>


namespace Fazel
{
	class WindowsWindow : public Window
	{
	public:
		explicit WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow() = default;

		auto OnUpdate() -> void override;

		inline auto GetWidth() const -> unsigned int override
		{
			return data.width;
		}

		inline auto GetHeight() const -> unsigned int override
		{
			return data.height;
		}

		inline auto SetEventCallback(const EventCallbackFn& callback) -> void override
		{
			data.eventCallback = callback;
		}

		auto SetVSync(bool enabled) -> void override;
		auto IsVSync() const -> bool override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* window;

		struct WindowData
		{
			std::string title;
			unsigned int width;
			unsigned int height;
			bool vSync;
			EventCallbackFn eventCallback;
		};

		WindowData data;
	};
}

