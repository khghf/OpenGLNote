#pragma once
#include<DM.h>
#include"Event/Event.h"
namespace DM
{
	class Listener:public BaseDelegate<void(Event*const)>
	{
		friend class Disptcher;
		friend class EventManager;
	};
}
