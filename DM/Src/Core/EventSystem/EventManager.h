#pragma once
#include<DM.h>
#include<ISingletion.h>
#include"Event/Event.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Event/WindowEvent.h"
#include"Disptcher.h"
#include"Listener.h"
namespace DM
{
	class DM_API EventManager:public ISingletion<EventManager>
	{
		friend class ISingletion<EventManager>;
	public:
		~EventManager() = default;
	private:
		EventManager();
		void Init();
	public:
		void OnEvent(Event* const e);
		template<class EventClass, class Class>
		void Register(SPtr<Class>Obj, void(Class::* MebFunType)( Event* const));
		template<class EventClass>
		void Register(void(*FunType)( Event* const));
		template<class EventClass,class LambdaType>
		void Register(LambdaType&& lam);

		template<class EventClass, class Class>
		void UnRegister(SPtr<Class>Obj, void(Class::* MebFunType)(Event* const));
		template<class EventClass>
		void UnRegister(void(*FunType)(Event* const));
		template<class EventClass, class LambdaType>
		void UnRegister(LambdaType&& lam);
	private:
		template<class EventClass>
		void RegisterInternal(Listener&&Lis);
		template<class EventClass>
		void UnRegisterInternal(Listener Lis);
	private:
		UnOrderedMap<EEventType, Disptcher>Disptchers;
	};
	template<class EventClass, class Class>
	inline void EventManager::Register(SPtr<Class>Obj, void(Class::* MebFunType)( Event* const))
	{
		Listener lis;
		lis.BindMebFun(Obj, MebFunType);
		this->RegisterInternal<EventClass>(std::move(lis));
	}
	template<class EventClass>
	inline void EventManager::Register(void(*FunType)( Event* const))
	{
		Listener lis;
		lis.BindFun(FunType);
		this->RegisterInternal<EventClass>(std::move(lis));
	}
	template<class EventClass,class LambdaType>
	inline void EventManager::Register(LambdaType&&lam)
	{
		Listener lis;
		lis.BindLamFun(std::forward<LambdaType>(lam));
		this->RegisterInternal<EventClass>(std::move(lis));
	}

	template<class EventClass, class Class>
	inline void EventManager::UnRegister(SPtr<Class>Obj, void(Class::* MebFunType)(Event* const))
	{
		Listener lis;
		lis.BindMebFun(Obj, MebFunType);
		this->UnRegisterInternal<EventClass>(lis);
	}
	template<class EventClass>
	inline void EventManager::UnRegister(void(*FunType)(Event* const))
	{
		Listener lis;
		lis.BindFun(FunType);
		this->UnRegisterInternal<EventClass>(lis);
	}
	template<class EventClass, class LambdaType>
	inline void EventManager::UnRegister(LambdaType&& lam)
	{
		Listener lis;
		lis.BindLamFun(std::forward<LambdaType>(lam));
		this->UnRegisterInternal<EventClass>(lis);
	}
	
	template<class EventClass>
	inline void EventManager::RegisterInternal(Listener&& Lis)
	{
		if (EventClass::GetStaticType() == EEventType::None)return;
		if (Disptchers.find(EventClass::GetStaticType()) == Disptchers.end())return;
		Disptchers[EventClass::GetStaticType()].AddListener(std::move(Lis));
	}
	template<class EventClass>
	inline void EventManager::UnRegisterInternal(Listener Lis)
	{
		if (EventClass::GetStaticType() == EEventType::None)return;
		if (Disptchers.find(EventClass::GetStaticType()) == Disptchers.end())return;
		Disptchers[EventClass::GetStaticType()].RemoveListener(Lis);
	}
}
