#pragma once
#include"BaseDelegate.h"
#include<vector>
#include<memory>
#include<unordered_set>
#include"DelegateHash.h"
template<typename FunType,typename T=void>
class MultiDelegate;
template<typename Ret,typename...Args, typename T>
class MultiDelegate<Ret(Args...),T>
{
private:
	std::vector<BaseDelegate<Ret(Args...)>>Delegates;
	//using KeySet=unord
	//unordered_set<>
	template<typename Class>
	using DelegateKeySet = std::unordered_set<DelegateKey<Class,Ret,Args...>, FDelegateKeyHash<Class, Ret, Args...>, FDelegateKeyEqual<Class, Ret, Args...>>;
	using FunType = Ret(*)(Args...);
	//DelegateKeySet KeySet;
public:
	MultiDelegate() = default;
	//普通函数
	void Add(FunType Fun)
	{
		/*DelegateKey<Ret, Args...>Key = Fun;
		if (KeySet.count(Key))return;*/
		BaseDelegate<Ret(Args...)>BD;
		BD.BindFun(std::forward<FunType>(Fun));
		Delegates.push_back(std::move(BD));
	}
	//成员函数
	template<typename Class>
	void Add(std::shared_ptr<Class>Obj, Ret(Class::*MebFunType)(Args...))
	{
		/*DelegateKey<Class,Ret, Args...>Key = MebFunType;
		if (KeySet.count(Key))return;*/
		BaseDelegate<Ret(Args...)>BD;
		BD.BindMebFun(std::forward<std::shared_ptr<Class>>(Obj), std::forward<Ret(Class::*)(Args...)>(MebFunType));
		Delegates.push_back(std::move(BD));
	}
	//Lambda表达式
	template<typename CallObj>
	void Add(CallObj&&Obj)
	{
		/*DelegateKey<Ret, Args...>Key = std::forward<CallObj>(Obj);
		if (KeySet.count(Key))return;*/
		BaseDelegate<Ret(Args...)>BD;
		BD.BindLamFun(std::forward<CallObj>(Obj));
		Delegates.push_back(std::move(BD));
	}
	void BroadCast(Args...arg)
	{
		for (const auto& DG : Delegates)
		{
			if (DG.IsValid())
			{
				DG.Execute(std::forward<Args>(arg)...);
			}
		}
	}
};