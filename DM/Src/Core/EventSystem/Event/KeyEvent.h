#pragma once
#include"Event.h"
#include<DM.h>
namespace DM
{
	using Key = int;
	class DM_API KeyEvent :public Event
	{
	public:
		
		static constexpr EEventType GetStaticType() {return Type;}
		virtual EEventType GetType()const override { return Type;}
		KeyEvent() = default;
		struct FEventData
		{
			Key key;
		};
		FEventData Data;
	private:
		static constexpr EEventType Type = EEventType::KeyEvent;
	};
	class DM_API KeyClick :public KeyEvent
	{
	public:
	};
	class DM_API KeyPress :public KeyClick
	{
	public:
	};
	class DM_API KeyRepeat :public KeyClick
	{
	public:
	};
	class DM_API KeyRelease :public KeyClick
	{
	public:
	};
}
