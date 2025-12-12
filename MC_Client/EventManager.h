#pragma once
#include"IManager.h"
class EventManager :public ISingletion<EventManager>
{




public:
	void RegisterEvent();
private:
	EventManager() = default;
	EventManager(const EventManager&) = delete;
	EventManager(EventManager& ) = delete;
	EventManager(EventManager&& ) = delete;
	EventManager& operator=(EventManager&) = delete;
	EventManager& operator=(EventManager&&) = delete;
};