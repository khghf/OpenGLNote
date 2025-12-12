#pragma once
#include<typeinfo>
#include<type_traits>
#include<unordered_set>
#include<variant>
template<typename T>
struct FTypeHash
{
	size_t operator()()const
	{
		return typeid(T).hash_code();
	}
};
template<typename T>
struct FLambdaHash
{
	size_t operator()(const T& lambda)const
	{
		size_t TypeHash = FTypeHash<T>()();
		size_t Obj_Hash = std::hash<T>()(lambda);
		return TypeHash ^ (Obj_Hash << 1);
	}
};
template<typename Class,typename Ret,typename ...Args>
struct FMebFunHash
{
	size_t operator()(Ret(Class::*MebFun)(Args...))const
	{
		size_t TypeHash = FTypeHash<Class>()();
		size_t MebFunHash = std::hash<void*>()(reinterpret_cast<void*>(MebFun));
		return TypeHash ^ (MebFunHash << 1);
	}
};
template<typename Class,typename Ret,typename...Args>
using DelegateKey = std::variant<
Ret(*)(Args...),
Ret(Class::*)(Args...),
std::any
>;
template<typename Class,typename Ret,typename...Args>
struct FDelegateKeyHash
{
	size_t operator()(const DelegateKey<Class, Ret, Args...>& DelegateKey)const
	{
		return std::visit(
			[](const auto&val) 
			{
				using Type = std::decay_t<decltype(val)>;
				if constexpr (std::is_function_v<Type>)
				{
					return std::hash<void*>()(reinterpret_cast<void*>(val));
				}
				else if constexpr (std::is_same_v<Type, std::any>)
				{
					const auto& lambda = std::any_cast<const auto &>(val);
					return FLambdaHash<decltype(lambda)>()(lambda);
				}
				else if constexpr (std::is_member_function_pointer_v<Type>)
				{
					return FMebFunHash<Class, Ret, Args...>()(val);
				}
				else
				{
					//static_assert(false, "FDelegateKeyHash:unkonw key type");
				}
			
			}, DelegateKey);
	}
};
template<typename Class, typename Ret, typename...Args>
struct FDelegateKeyEqual 
{
	bool operator()(const DelegateKey<Class,Ret,Args...>& a, const DelegateKey<Class, Ret,Args...>& b) const
	{
		if (a.index() != b.index()) return false; // 类型不同，直接不相等
		return std::visit([](const auto& val_a, const auto& val_b) -> bool 
			{
				using T_a = std::decay_t<decltype(val_a)>;
				using T_b = std::decay_t<decltype(val_b)>;
				if constexpr (std::is_function_v<T_a>)
				{
					return std::hash<void*>()(reinterpret_cast<void*>(val_a)) == std::hash<void*>()(reinterpret_cast<void*>(val_b));
				}
				else if constexpr (std::is_same_v<T_a, std::any>) 
				{
					const auto& lambda_a = std::any_cast<const auto&>(val_a);
					const auto& lambda_b = std::any_cast<const auto&>(val_b);
					using LambdaType_a = decltype(lambda_a);
					using LambdaType_b = decltype(lambda_b);
					return FLambdaHash<LambdaType_a>()(lambda_a) == FLambdaHash<LambdaType_b>()(lambda_b);
				}
				else if constexpr (std::is_same_v<T_a, size_t>) 
				{
					return FMebFunHash<Class, Ret, Args...>()(val_a) == FMebFunHash<Class, Ret, Args...>()(val_b);
				}
				return false;
			}, a, b);
	}
};