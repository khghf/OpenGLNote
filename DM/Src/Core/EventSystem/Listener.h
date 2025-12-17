#pragma once
#include<DM.h>
#include"Event/Event.h"
namespace DM
{
	class Listener
	{
		friend class Disptcher;
		friend class EventManager;
	private:
		using Callable = BaseDelegate<void(const Event*const)>;
		Callable CallObj;
		Listener(Callable&& b) :CallObj(std::move(b)) {}
		void OnEvent(const Event* const e)const
		{
			CallObj.Execute(e);
		}
	};
}
