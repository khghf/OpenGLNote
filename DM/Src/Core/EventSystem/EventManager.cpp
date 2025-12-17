#include "DMPCH.h"
#include "EventManager.h"
namespace DM
{
	EventManager::EventManager()
	{
		Init();
	}
	void EventManager::Init()
	{
		Disptchers[EEventType::KeyEvent] = Disptcher();
		Disptchers[EEventType::MouseEvent] = Disptcher();
		Disptchers[EEventType::WindowEvent] = Disptcher();
	}
	void EventManager::OnEvent(const Event* const e)
	{
		const auto& it = Disptchers.find(e->GetType());
		if (it == Disptchers.end())return;
		it->second.OnEvent(e);
	}
}


