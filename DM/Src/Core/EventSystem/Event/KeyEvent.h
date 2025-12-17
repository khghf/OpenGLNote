#pragma once
#include"Event.h"
#include<DM.h>
namespace DM
{
	using Key = int;
	class  KeyEvent :public Event
	{
	public:
		
		static constexpr EEventType GetStaticType() {return Type;}
		virtual EEventType GetType()const override { return Type;}
		KeyEvent() = default;

	private:
		static constexpr EEventType Type = EEventType::KeyEvent;
	};
	class  KeyClick :public KeyEvent
	{
	public:
		enum Action
		{
			None=-1,
			Release,
			Press,
			Repate,
			
		};
		struct FEventData
		{
			Key key;
			Action KeyAction = Action::None;
		};
		FEventData Data;
	};
	
}
