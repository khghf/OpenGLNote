#pragma once
#include<DM.h>
#include<ISingletion.h>
#include"Listener.h"
namespace DM
{
	class Disptcher:public MultiDelegate<void(Event*const)>
	{
		friend class EventManager;
	private:
		void Disptch( Event* const e)
		{
			this->BroadCast(e);
		}
		void AddListener(Listener&&l)
		{
			this->Add(static_cast<BaseDelegate<void(Event* const)>>(l));
		}
		void RemoveListener(Listener l)
		{
			this->Remove(l);
		}
	};
}
