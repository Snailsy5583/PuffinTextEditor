//
// Created by r6awe on 8/14/2025.
//

#ifndef PUFFINTEXTEDITOR_KEYBOARDEVENTS_H
#define PUFFINTEXTEDITOR_KEYBOARDEVENTS_H

#include "Events.h"

namespace Engine
{
	class KeyboardCharTypedEvent : public Event
	{
	public:
		explicit KeyboardCharTypedEvent(const Window &window, unsigned int cp) :
			Event(window), m_Char((char) cp)
		{
		}

		char GetChar() const { return m_Char; }

	public:
		static EventType GetStaticType()
		{
			return EventType::KeyboardCharTyped;
		}
		EventType GetEventType() const override
		{
			return KeyboardCharTypedEvent::GetStaticType();
		}

		virtual const char *GetName() const override
		{
			return "KeyboardCharTyped";
		}

	private:
		char m_Char;
	};

	class KeyboardEvent : public Event
	{
	public:
		virtual int GetKey() const { return m_Key; }
		virtual int GetPhysicalKey() const { return m_PhysicalKey; }
		virtual int GetModifiers() const { return m_Modifiers; }

	protected:
		KeyboardEvent(const Window &window, int key, int scancode, int mods) :
			Event(window), m_Key(key), m_PhysicalKey(scancode),
			m_Modifiers(mods)
		{
		}

	protected:
		int m_Key, m_PhysicalKey, m_Modifiers;
	};

	class KeyboardKeyPressedEvent : public KeyboardEvent
	{
	public:
		KeyboardKeyPressedEvent(const Window &window, int key, int scancode,
								int mods) :
			KeyboardEvent(window, key, scancode, mods)
		{
		}

		static EventType GetStaticType()
		{
			return EventType::KeyboardKeyPressed;
		}
		EventType GetEventType() const override
		{
			return KeyboardKeyPressedEvent::GetStaticType();
		}

		virtual const char *GetName() const override
		{
			return "KeyboardKeyPressed";
		}
	};

	class KeyboardKeyReleasedEvent : public KeyboardEvent
	{
	public:
		KeyboardKeyReleasedEvent(const Window &window, int key, int scancode,
								 int mods) :
			KeyboardEvent(window, key, scancode, mods)
		{
		}

		static EventType GetStaticType()
		{
			return EventType::KeyboardKeyReleased;
		}
		EventType GetEventType() const override
		{
			return KeyboardKeyReleasedEvent::GetStaticType();
		}

		virtual const char *GetName() const override
		{
			return "KeyboardKeyReleased";
		}
	};

	class KeyboardKeyRepeatedEvent : public KeyboardEvent
	{
	public:
		KeyboardKeyRepeatedEvent(const Window &window, int key, int scancode,
								 int mods) :
			KeyboardEvent(window, key, scancode, mods)
		{
		}

		static EventType GetStaticType()
		{
			return EventType::KeyboardKeyRepeated;
		}
		EventType GetEventType() const override
		{
			return KeyboardKeyRepeatedEvent::GetStaticType();
		}

		virtual const char *GetName() const override
		{
			return "KeyboardKeyRepeated";
		}
	};


}	 // namespace Engine

#endif	  // PUFFINTEXTEDITOR_KEYBOARDEVENTS_H
