#pragma once
#include<memory>
#include"DelegateInstance.h"
template<typename FunType,typename T=void>
class BaseDelegate;

template<typename Ret,typename...Args,typename T>
class BaseDelegate<Ret(Args...),T>
{
	std::unique_ptr<IDelegateInstance<Ret, Args...>>DelegateInstance;
	using FunType = Ret(*)(Args...);
public:
	BaseDelegate() noexcept = default;
	BaseDelegate(BaseDelegate&&)noexcept = default;
	BaseDelegate& operator=(BaseDelegate&&)noexcept = default;
	BaseDelegate(const BaseDelegate&) = delete;
	BaseDelegate& operator=(BaseDelegate&)= delete;
	void BindFun(const FunType& Fun)
	{
		DelegateInstance = std::make_unique<FunDelegateInst<Ret, Args...>>(Fun);
	}
	void BindStaticFun(const FunType& Fun)
	{
		DelegateInstance = std::make_unique<StaticFunDelegateInst<Ret, Args...>>(Fun);
	}
	template<typename Class>
	void BindMebFun(std::shared_ptr<Class>Obj,Ret(Class::*MebFunType)(Args...))
	{
		DelegateInstance = std::make_unique<MebFunDelegateInst<Class,Ret, Args...>>(Obj,MebFunType);
	}
	template<typename CallObj>
	void BindLamFun(CallObj&& Obj)
	{
		DelegateInstance = std::make_unique<LambdaDelegateInst<CallObj, Ret, Args...>>(std::forward<CallObj>(Obj));
	}
	Ret Execute(Args... arg)const
	{
		if (DelegateInstance)
		{
			return DelegateInstance->Execute(std::forward<Args>(arg)...);
		}
		else
		{
			throw std::runtime_error("Delegate is not bound to any callable");
		}
	}
	bool IsValid()const
	{
		if (DelegateInstance)return true;
		return false;
	}
};