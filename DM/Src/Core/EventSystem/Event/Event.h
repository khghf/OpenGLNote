#pragma once
#include<Core/Core.h>

namespace DM
{
	enum class EEventType
	{
		None,
		Event,
		MouseEvent,
		KeyEvent,
		WindowEvent
	};
	class DM_API Event
	{
	public:
		struct FEventData {};
		FEventData Data;
		template<class EventClass>
		typename const EventClass::FEventData* GetData()const;
 		static constexpr EEventType GetStaticType(){ 
			return Type; 
		}
		virtual EEventType GetType()const = 0;
		std::string_view Name = "BaseEvent";
		virtual ~Event()=default;
		bool bHandled = false;
	protected:
		static constexpr EEventType Type=EEventType::Event;
	};

}


