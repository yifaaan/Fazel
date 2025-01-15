#pragma once

#include "Fazel/Core.h"

#include "spdlog/fmt/ostr.h"

#include <string>
#include <functional>

namespace Fazel
{
	// Events in Fazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and mut be deal with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		// --------Window--------
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		// --------App-----------
		AppTick,
		AppUpdate,
		AppRender,
		// --------Key-----------
		KeyPressed,
		KeyReleased,
		// --------Mouse---------
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled,
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
	};


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVETN_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
	
	
	class FAZEL_API Event
	{

	public:
		virtual EventType GetEventType()	const = 0;
		virtual const char* GetName()		const = 0;
		virtual int GetCategoryFlags()		const = 0;
		virtual std::string ToString()		const { return GetName(); }


		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& _event) : event(_event) { }

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (event.GetEventType() == T::GetStaticType())
			{
				event.handled = func(dynamic_cast<T&>(event));
				return true;
			}
			return false;
		}

	private:
		Event& event;
	};


	std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}

