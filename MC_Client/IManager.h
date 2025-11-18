#pragma once
#include<DataType.h>
template<typename T>
class ISingletion
{
public:
	ISingletion() {}
	static SPtr<T>GetSingletion()
	{
		static SPtr<T>Instance;
		if (Instance == nullptr)
		{
			Instance = std::shared_ptr<T>(new T());
		}
		return Instance;
	}
	~ISingletion() {}
};