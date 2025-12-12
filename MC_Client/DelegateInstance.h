#pragma once
#include<memory>
template<typename Ret, typename...Args>
class IDelegateInstance
{
public:
	~IDelegateInstance() = default;
	virtual Ret Execute(Args...arg)const = 0;
};
//普通函数
template<typename Ret,typename...Args>
class FunDelegateInst :public IDelegateInstance<Ret,Args...>
{
private:
	using FunType = Ret(*)(Args...);
	FunType Fun;
public:
	FunDelegateInst(FunType Fun) :Fun(Fun) {}
	virtual Ret Execute(Args...arg)const override
	{
		return Fun(std::forward<Args>(arg)...);
	}
};
//静态函数
template<typename FunObj, typename Ret, typename...Args>
using StaticFunDelegateInst = FunDelegateInst<FunObj, Ret, Args...>;
//成员函数
template<typename Class, typename Ret, typename...Args>
class MebFunDelegateInst :public IDelegateInstance<Ret, Args...>
{
private:
	std::weak_ptr<Class>Obj=nullptr;
	using FunType = Ret(Class::*)(Args...);
	FunType Fun;
public:
	MebFunDelegateInst(std::shared_ptr<Class>Obj, FunType Fun) :Obj(Obj),Fun(Fun) {}
	virtual Ret Execute(Args...arg)const override
	{
		if (const auto& element = Obj.lock())
		{
			return (element.get()->*Fun)(std::forward<Args>(arg)...);
		}
		else
		{
			assert(false&&"Delegate:Bound Object was destroied");
		}
		return Ret{};
	}
};
template<typename CallObj,typename Ret,typename...Args>
class LambdaDelegateInst :public IDelegateInstance<Ret, Args...>
{
private:
	CallObj Obj;
public:
	LambdaDelegateInst(CallObj&& Obj) :Obj(std::forward<CallObj>(Obj)) {}
	virtual Ret Execute(Args...arg)const override
	{
		return Obj(std::forward<Args>(arg)...);
	}
};