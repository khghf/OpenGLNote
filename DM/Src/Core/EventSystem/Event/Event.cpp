#include<DMPCH.h>
#include"Event.h"
#include"KeyEvent.h"
#include"MouseEvent.h"
#include"WindowEvent.h"
namespace DM
{
	template<>
	DM_API const KeyClick::FEventData* Event::GetData<KeyClick>()const
	{
		const KeyClick* e = static_cast<const KeyClick*>(this);
		return &e->Data;
	}
	template<>
	DM_API const MouseClick::FEventData* Event::GetData<MouseClick>()const
	{
		const MouseClick* e = static_cast<const MouseClick*>(this);
		return &e->Data;
	}
	template<>
	DM_API const WindowResizeEvent::FEventData* Event::GetData<WindowResizeEvent>()const
	{
		const WindowResizeEvent* e = static_cast<const WindowResizeEvent*>(this);
		return &e->Data;
	}
}