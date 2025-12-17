#pragma once
#include<DM.h>
namespace DM
{
	enum class EEventType
	{
		None,
		MouseEvent,
		KeyEvent,
		WindowEvent
	};
	class DM_API Event
	{
	public:
		template<class EventClass>
		typename const EventClass::FEventData* GetData()const;
 		static constexpr EEventType GetStaticType(){ 
			return Type; 
		}
		virtual EEventType GetType()const = 0;
		std::string_view Name = "BaseEvent";
	protected:
		static constexpr EEventType Type=EEventType::None;
	};

}


