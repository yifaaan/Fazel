#pragma once

#include "Event.h"

#include <sstream>

namespace Fazel
{
	class FAZEL_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			:mouseX(x)
			,mouseY(y)
		{ }

		inline float GetX() const { return mouseX; }
		inline float GetY() const { return mouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mouseX << ", " << mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVETN_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float mouseX;
		float mouseY;
	};

	class FAZEL_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float _XOffset, float _YOffset)
			:XOffset(_XOffset)
			,YOffset(_YOffset)
		{ }

		inline float GetXOffset() const { return XOffset; }
		inline float GetYOffset() const { return YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVETN_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float XOffset;
		float YOffset;
	};

	class FAZEL_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return button; }

		EVETN_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int _button)
			:button(_button)
		{ }

		int button;
	};

	class FAZEL_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		explicit MouseButtonPressedEvent(int button)
			:MouseButtonEvent(button)
		{ }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class FAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		explicit MouseButtonReleasedEvent(int button)
			:MouseButtonEvent(button)
		{ }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}