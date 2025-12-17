#pragma once
#include"Event.h"
#include<DM.h>
namespace DM
{
	using Key = int;
	class  MouseEvent :public Event
	{
	public:
		static constexpr EEventType GetStaticType() { return Type; }
		virtual EEventType GetType()const override { return Type; }
		MouseEvent() = default;
		enum Action
		{
			None,
			Press,
			Repate,
			Release,
		};
		struct FEventData
		{
			Vector2<double> vec2;
			Action KeyAction;
			Key key;
		};
		FEventData Data;
	private:
		static constexpr EEventType Type = EEventType::MouseEvent;
	};
	class  MouseClick :public MouseEvent
	{
	
	};
	using MouseDown = MouseClick;
	using MouseUp = MouseClick;
	class  MouseMove :public MouseEvent
	{
	
	};
	class  MouseScroll :public MouseEvent
	{

	};
}
