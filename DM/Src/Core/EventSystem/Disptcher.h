#pragma once
#include<Core/DelegateSystem/MultiDelegate.h>
#include<ISingletion.h>
#include"Listener.h"
namespace DM
{
	class Disptcher
	{
		friend class EventManager;
	public:
		Disptcher() = default;
		explicit Disptcher(Event* const e) :m_e(e) {}
		//分发给指定类型事件的单个监听m_e
		template<class T,class LambdaType>
		void Disptch(LambdaType&&Lam)
		{
			DisptchTarget.Bind(std::forward<LambdaType>(Lam));
			if (T::GetStaticType() == m_e->GetType())
			{
				m_e->bHandled = DisptchTarget.Execute(m_e);
			}
		}
		template<class T>
		void Disptch(bool(*Fun)(Event*const))
		{
			DisptchTarget.Bind(Fun);
			if (T::GetStaticType() == e->GetType())
			{
				m_e->bHandled = DisptchTarget.Execute(m_e);
			}
		}
	private:
		//分发给指定类型事件的所有监听EventToMD
		void OnEvent(Event* const e)
		{
			auto it = EventToMD.find(e->GetType());
			if (it == EventToMD.end())return;
			it->second.BroadCast(e);
		}
		template<class EventClass>
		void AddListener(Listener&&l)
		{
			auto it = EventToMD.find(EventClass::GetStaticType());
			EventToMD[EventClass::GetStaticType()].Add(static_cast<BaseDelegate<void(Event* const)>>(l));
		}
		template<class EventClass>
		void RemoveListener(Listener l)
		{
			auto it = EventToMD.find(EventClass::GetStaticType());
			if (it == EventToMD.end())return;
			it->second.Remove(l);
		}
	private:
		Event* m_e=nullptr;
		BaseDelegate<bool(Event* const)>DisptchTarget;
		UnOrderedMap<EEventType, MultiDelegate<void(Event* const)>>EventToMD;
	};
}
