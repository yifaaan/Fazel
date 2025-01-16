#pragma once

#include "fzpch.h"

#include "Fazel/Core.h"
#include "Fazel/Events/Event.h"

namespace Fazel
{
	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& _title = "Fazel Engine", unsigned int _width = 1280, unsigned int _height = 720)
			:title(_title)
			,width(_width)
			,height(_height)
		{ }
	};
	
	/// Interface representing a desktop system based Window
	class FAZEL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual auto OnUpdate() -> void = 0;

		virtual auto GetWidth() const -> unsigned int = 0;
		virtual auto GetHeight() const -> unsigned int = 0;

		virtual auto SetEventCallback(const EventCallbackFn& callback) -> void = 0;
		virtual auto SetVSync(bool enable) -> void = 0;
		virtual auto IsVSync() const -> bool = 0;

		static Window* Create(const WindowProps& props = WindowProps{});
	};
}