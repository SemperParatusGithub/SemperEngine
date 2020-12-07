#pragma once

#include "Event.h"
#include "SemperEngine/Core/KeyCodes.h"

namespace SemperEngine
{

	class KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(const KeyCode keycode)
			: m_KeyCode(keycode) {}

		KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, const uint16_t repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		uint16_t GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}
		static EventType	GetStaticType()						{ return EventType::KeyPressed;		}
		virtual EventType	GetEventType()		const override	{ return GetStaticType();			}
		virtual const char *GetName()			const override	{ return "KeyPressed";				}

	private:
		uint16_t m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		static EventType	GetStaticType()						{ return EventType::KeyReleased;	}
		virtual EventType	GetEventType()		const override	{ return GetStaticType();			}
		virtual const char *GetName()			const override	{ return "keyReleased";				}
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		static EventType	GetStaticType()						{ return EventType::KeyTyped;		}
		virtual EventType	GetEventType()		const override	{ return GetStaticType();			}
		virtual const char *GetName()			const override	{ return "KeyTyped";				}
	};
}