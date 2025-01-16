#pragma once

#include "Event.h"

namespace Fazel
{
	class FAZEL_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return keyCode; }

		EVETN_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		explicit KeyEvent(int _keyCode) : keyCode(_keyCode) { }

		int keyCode;
	};

	class FAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int _keyCode, int _repeatCount)
			:KeyEvent(_keyCode)
			,repeatCount(_repeatCount) 
		{ }

		inline int GetRepeatCount() const { return repeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int repeatCount;
	};

	class FAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int _keyCode, int _repeatCount)
			:KeyEvent(_keyCode) { }


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};
}