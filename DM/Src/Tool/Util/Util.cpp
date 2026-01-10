#include "DMPCH.h"
#include "Util.h"
#include<codecvt>
#include<locale>
namespace DM
{

	std::string Util::WStringToString_U8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>>wcv;
		return wcv.to_bytes(str);
	}

	std::wstring Util::StringToWString_U8(const std::string& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>>wcv;
		return wcv.from_bytes(str);;
	}
}