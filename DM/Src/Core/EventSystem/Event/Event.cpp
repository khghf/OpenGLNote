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
	assert(e->GetType()==EventClass::GetStaticType()&&"不能获取其它类型的数据");\
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
	EventGetDataSpawn(KeyTyped);
	//**************************MouseEvent
	EventGetDataSpawn(MouseClick);
	EventGetDataSpawn(MousePress);
	EventGetDataSpawn(MouseRelease);
	EventGetDataSpawn(MouseMove); 
	EventGetDataSpawn(MouseScroll);
	//**************************WindowEvent
	EventGetDataSpawn(WindowResize);
	EventGetDataSpawn(WindowClose);
}