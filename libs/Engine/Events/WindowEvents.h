#pragma once

#include "Events.h"

namespace Engine
{


	class WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent(const Window &window) : Event(window) {}

		static EventType GetStaticType() { return EventType::WindowClosed; }

		virtual EventType GetEventType() const override
		{
			return WindowClosedEvent::GetStaticType();
		}

		virtual const char *GetName() const { return "WindowClosed"; }
	};

	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(const Window &window, int width, int height) :
			Event(window), m_Width(width), m_Height(height)
		{
		}

		static EventType GetStaticType() { return EventType::WindowResized; }

		virtual EventType GetEventType() const override
		{
			return WindowResizedEvent::GetStaticType();
		}

		virtual const char *GetName() const { return "WindowResized"; }

		int GetWidth() const { return m_Width; }

		int GetHeight() const { return m_Height; }

	private:
		int m_Width, m_Height;
	};


}	 // namespace Engine