#pragma once

#include "Event.h"

#include <sstream>


namespace Fazel
{
	class FAZEL_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int _width, unsigned int _height)
			:width(_width)
			,height(_height)
		{ }

		inline unsigned int GetWidth() const { return width; }
		inline unsigned int GetHeight() const { return height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << width << ", " << height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVETN_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int width;
		unsigned int height;
	};


	class FAZEL_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVETN_CLASS_CATEGORY(EventCategoryApplication)
	};

	class FAZEL_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVETN_CLASS_CATEGORY(EventCategoryApplication)
	};

	class FAZEL_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
			EVETN_CLASS_CATEGORY(EventCategoryApplication)
	};

	class FAZEL_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
			EVETN_CLASS_CATEGORY(EventCategoryApplication)
	};
}