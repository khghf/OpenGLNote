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
		void OnEvent(const Event* const e);
		template<class EventClass, class Class>
		void RegisterMebFun(SPtr<Class>Obj, void(Class::* MebFunType)(const Event* const));
		template<class EventClass>
		void RegisterFun(void(*MebFunType)(const Event* const));
		template<class EventClass,class LambdaType>
		void RegisterLam(LambdaType&& lam);
		template<class EventClass>
		void UnRegister();
	private:
		template<class EventClass>
		void RegisterInternal(BaseDelegate<void(const Event* const)>&&BD);
	private:
		UnOrderedMap<EEventType, Disptcher>Disptchers;
	};
	template<class EventClass, class Class>
	inline void EventManager::RegisterMebFun(SPtr<Class>Obj, void(Class::* MebFunType)(const Event* const))
	{
		BaseDelegate<void(const Event* const)>BD;
		BD.BindMebFun(Obj, MebFunType);
		this->RegisterInternal<EventClass>(std::move(BD));
	}
	template<class EventClass>
	inline void EventManager::RegisterFun(void(*MebFunType)(const Event* const))
	{
		BaseDelegate<void(const Event* const)>BD;
		BD.BindFun(MebFunType);
		this->RegisterInternal<EventClass>(std::move(BD));
	}
	template<class EventClass,class LambdaType>
	inline void EventManager::RegisterLam(LambdaType&&lam)
	{
		BaseDelegate<void(const Event* const)>BD;
		BD.BindLamFun(std::move(lam));
		this->RegisterInternal<EventClass>(std::move(BD));
	}
	template<class EventClass>
	inline void EventManager::UnRegister()
	{

	}
	template<class EventClass>
	inline void EventManager::RegisterInternal(BaseDelegate<void(const Event* const)>&& BD)
	{
		if (EventClass::GetStaticType() == EEventType::None)return;
		if (Disptchers.find(EventClass::GetStaticType()) == Disptchers.end())return;
		Disptchers[EventClass::GetStaticType()].AddListener(Listener(std::move(BD)));
	}
}
