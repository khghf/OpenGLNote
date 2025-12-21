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
		Disptchers[EEventCategory::Event] = Disptcher();
		Disptchers[EEventCategory::KeyEvent] = Disptcher();
		Disptchers[EEventCategory::MouseEvent] = Disptcher();
		Disptchers[EEventCategory::WindowEvent] = Disptcher();
	}
	void EventManager::OnEvent( Event* const e)
	{
		Disptchers[EEventCategory::Event].OnEvent(e);
		const auto& it = Disptchers.find(e->GetCategory());
		if (it == Disptchers.end()|| e->GetCategory()== EEventCategory::Event)return;
		it->second.OnEvent(e);
	}
}


