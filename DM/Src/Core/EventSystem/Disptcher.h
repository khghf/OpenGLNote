#pragma once
#include<Core/DelegateSystem/MultiDelegate.h>
#include<Tool/ISingletion.h>
#include"Listener.h"
namespace DM
{
	class Disptcher
	{
		friend class EventManager;
	public:
		Disptcher() = default;
		explicit Disptcher(Event* const e) :m_e(e) {}
		//分发给指定类型事件的单个监听DisptchTarget lambda
		template<class SpecifiedEvent,class LambdaType>
		void DisptchSpecifiedEvent(LambdaType&&Lam)
		{
			DisptchTarget.Bind(std::forward<LambdaType>(Lam));
			if (SpecifiedEvent::GetStaticType() == m_e->GetType())
			{
				DisptchTarget.Execute(m_e);
			}
		}
		//分发给指定类型事件的单个监听DisptchTarget 函数指针
		template<class SpecifiedEvent>
		void DisptchSpecifiedEvent(void(*Fun)(Event*const))
		{
			DisptchTarget.Bind(Fun);
			if (SpecifiedEvent::GetStaticType() == m_e->GetType())
			{
				DisptchTarget.Execute(m_e);
			}
		}
	private:
		//分发给指定类型事件的所有监听EventToMD
		void OnEvent(Event* const e)
		{
			/*auto it = EventToMD.find(e->GetType());
			if (it == EventToMD.end())return;
			it->second.BroadCast(e);*/
			MD.BroadCast(e);
		}
		//template<class EventClass>
		void AddListener(Listener&&l)
		{
			//EventToMD[EventClass::GetStaticType()].Add(static_cast<BaseDelegate<void(Event* const)>>(l));
			MD.Add(static_cast<BaseDelegate<void(Event* const)>>(l));
		}
		//template<class EventClass>
		void RemoveListener(Listener l)
		{
			/*auto it = EventToMD.find(EventClass::GetStaticType());
			if (it == EventToMD.end())return;
			it->second.Remove(l);*/
			MD.Remove(l);
		}
	private:
		Event* m_e=nullptr;
		BaseDelegate<void(Event* const)>DisptchTarget;
		//UnOrderedMap<EEventType, MultiDelegate<void(Event* const)>>EventToMD;
		MultiDelegate<void(Event* const)>MD;
	};
}
