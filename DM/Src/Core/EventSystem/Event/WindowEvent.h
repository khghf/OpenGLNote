#pragma once
#include"Event.h"
#include<DM.h>
namespace DM
{
	class  WindowEvent :public Event
	{
	public:
		static constexpr EEventType GetStaticType() { return Type; }
		virtual EEventType GetType()const override { return Type; }
		WindowEvent() = default;
	private:
		static constexpr EEventType Type = EEventType::WindowEvent;
	};
	class  WindowResizeEvent :public WindowEvent
	{
	public:
		struct FEventData
		{
			Vector2<double> Size;
		};
		FEventData Data;
	};
	
}
