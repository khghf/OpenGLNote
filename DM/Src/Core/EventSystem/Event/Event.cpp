#include<DMPCH.h>
#include<Core/Core.h>
#include"Event.h"
#include"KeyEvent.h"
#include"MouseEvent.h"
#include"WindowEvent.h"
#define EventGetDataSpawn(EventClass) \
template<>\
DM_API const EventClass::FEventData*Event::GetData<EventClass>()const\
{\
	const EventClass* e = static_cast<const EventClass*>(this);\
	return &e->Data;\
}
namespace DM
{
	EventGetDataSpawn(Event);
	//**************************KeyEvent
	EventGetDataSpawn(KeyClick);
	EventGetDataSpawn(KeyPress);
	EventGetDataSpawn(KeyRepeat);
	EventGetDataSpawn(KeyRelease);
	//**************************MouseEvent
	EventGetDataSpawn(MouseClick);
	EventGetDataSpawn(MousePress);
	EventGetDataSpawn(MouseRelease);
	//**************************WindowEvent
	EventGetDataSpawn(WindowResizeEvent);
}