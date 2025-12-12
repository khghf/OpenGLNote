#pragma once
class IEvent
{
	virtual ~IEvent();
};
class MouseEvent :public IEvent
{

	enum Type
	{
		Move,
		ButtonDown,
		ButtonUp,
		//s'call'l
	};
};