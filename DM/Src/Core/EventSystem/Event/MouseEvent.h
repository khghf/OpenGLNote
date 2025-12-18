#pragma once
#include"Event.h"
#include<DM.h>
namespace DM
{
	using Key = int;
	class DM_API MouseEvent :public Event
	{
	public:
		static constexpr EEventType GetStaticType() { return Type; }
		virtual EEventType GetType()const override { return Type; }
		MouseEvent() = default;
	private:
		static constexpr EEventType Type = EEventType::MouseEvent;
	};
	class DM_API MouseClick :public MouseEvent
	{
	public:
		struct FEventData
		{
			Vector2 pos;
			Key key;
		};
		FEventData Data;
	};
	class DM_API MousePress :public MouseClick
	{
	};
	class DM_API MouseRelease :public MouseClick
	{
	};
	class DM_API MouseMove :public MouseEvent
	{
	public:
		struct FEventData
		{
			Vector2 pos;
		};
		FEventData Data;
	};
	class DM_API MouseScroll :public MouseEvent
	{
	public:
		struct FEventData
		{
			Vector2 offset;
		};
		FEventData Data;
	};
}
