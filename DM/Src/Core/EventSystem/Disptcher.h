#pragma once
#include<DM.h>
#include<ISingletion.h>
#include"Listener.h"
namespace DM
{
	class Disptcher:public MultiDelegate<void(Event*const)>
	{
		friend class EventManager;
	public:
		Disptcher() = default;
		explicit Disptcher(Event* const e) :m_e(e) {}
		template<class T,class LambdaType>
		void Disptch(LambdaType&&Lam)
		{
			BD.Bind(std::forward<LambdaType>(Lam));
			if (T::GetStaticType() == m_e->GetType())
			{
				m_e->bHandled = BD.Execute(m_e);
			}
		}
		template<class T>
		void Disptch(bool(*Fun)(Event*const))
		{
			BD.Bind(Fun);
			if (T::GetStaticType() == e->GetType())
			{
				m_e->bHandled = BD.Execute(m_e);
			}
		}
	private:
		void OnEvent(Event* const e)
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
	private:
		Event* m_e=nullptr;
		BaseDelegate<bool(Event* const)>BD;
	};
}
