#pragma once
#include<DM.h>
#include<ISingletion.h>
#include"Listener.h"
namespace DM
{
	class Disptcher
	{
		friend class EventManager;
	private:
		MultiDelegate<void(const Event* const)>Listeners;
		void OnEvent(const Event* const e)
		{
			Listeners.BroadCast(e);
		}
		void AddListener(Listener&&l)
		{
			Listeners.Add(std::move(l.CallObj));
		}
	};
}
