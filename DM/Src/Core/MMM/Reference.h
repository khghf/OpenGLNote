#pragma once
#include<memory>
namespace DM
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T,typename...Args>
	inline Scope<T>CreateScope(Args&&...arg)
	{
		return std::make_unique<T>(std::forward<Args>(arg)...);
	}
	template<typename T>
	inline Scope<T>CreateScope(T* raw)
	{
		return std::unique_ptr<T>(raw);
	}


	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename...Args>
	inline Ref<T>CreateRef(Args&&...arg)
	{
		return std::make_shared<T>(std::forward<Args>(arg)...);
	}
	template<typename T>
	inline Ref<T>CreateRef(T*raw)
	{
		return std::shared_ptr<T>(raw);
	}


	template<typename T>
	using WRef = std::weak_ptr<T>;
	template<typename T>
	inline WRef<T>CreateWRef(Ref<T>ref)
	{
		return std::weak_ptr<T>(ref);
	}
	
}