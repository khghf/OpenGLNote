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
	using Ref = std::shared_ptr<T>;
	template<typename T, typename...Args>
	inline Ref<T>CreateRef(Args&&...arg)
	{
		return std::make_shared<T>(std::forward<Args>(arg)...);
	}
}