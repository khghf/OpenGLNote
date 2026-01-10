#pragma once
#include<string.h>
namespace DM
{
	class Util
	{
	public:
		static std::string WStringToString_U8(const std::wstring& str);
		static std::wstring StringToWString_U8(const std::string& str);
	};
}


