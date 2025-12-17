#pragma once
#include<iostream>
namespace Util
{
	template<typename...Args>
	void Print(Args...arg)
	{
		(std::cout << ...<< arg) << std::endl;
	} 
}