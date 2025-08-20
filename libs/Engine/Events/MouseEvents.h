#pragma once

// #include "../const Window.h"
#include "Events.h"

namespace Engine
{
	class MouseButtonEvent : public Event
	{
	public:
		void GetMousePosition(float &outX, float &outY)
		{
			outX = m_MousePosX;
			outY = m_MousePosY;
		}

		int GetMouseButton() { return m_Button; }

	protected:
		MouseButtonEvent(const Window &window, int button, float mouseX,
						 float mouseY) :
			Event(window),
			m_Button(button), m_MousePosX(mouseX), m_MousePosY(mouseY)
		{
		}

		int m_Button;
		float m_MousePosX, m_MousePosY;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const Window &window, int button, float mouseX,
								float mouseY) :
			MouseButtonEvent(window, button, mouseX, mouseY)
		{
		}

		static EventType GetStaticType()
		{
			return EventType::MouseButtonPressed;
		}

		EventType GetEventType() const override
		{
			return MouseButtonPressedEvent::GetStaticType();
		}

		virtual const char *GetName() const { return "MouseButtonPressed"; }
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const Window &window, int button, float mouseX,
								 float mouseY) :
			MouseButtonEvent(window, button, mouseX, mouseY)
		{
		}

		static EventType GetStaticType()
		{
			return EventType::MouseButtonReleased;
		}

		EventType GetEventType() const override
		{
			return MouseButtonReleasedEvent::GetStaticType();
		}

		virtual const char *GetName() const { return "MouseButtonReleased"; }
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const Window &window, float mouseX, float mouseY) :
			Event(window), m_MousePosX(mouseX), m_MousePosY(mouseY)
		{
		}

		static EventType GetStaticType() { return EventType::MouseMoved; }

		EventType GetEventType() const override
		{
			return MouseMovedEvent::GetStaticType();
		}

		virtual const char *GetName() const { return "MouseMoved"; }

		void GetMousePosition(float &outX, float &outY)
		{
			outX = m_MousePosX;
			outY = m_MousePosY;
		}

	private:
		float m_MousePosX, m_MousePosY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const Window &window, float x, float y) :
			Event(window), m_Delta(x, y)
		{
		}

		static EventType GetStaticType() { return EventType::MouseScrolled; }

		EventType GetEventType() const override
		{
			return MouseScrolledEvent::GetStaticType();
		}

		virtual const char *GetName() const { return "MouseScrolled"; }

		glm::vec2 GetScrollAmount() const { return m_Delta; }

	private:
		glm::vec2 m_Delta {};
	};

}	 // namespace Engine