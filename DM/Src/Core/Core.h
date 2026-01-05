#pragma once
#include"Log.h"
#include<string>
#ifdef DM_PLATFORM_WINDOWS
	#if DM_DMNAMIC_LINK
		#ifdef DM_BUILD_DLL
			#define DM_API __declspec(dllexport)
		#else
			#define DM_API __declspec(dllimport)
		#endif // DM_BUILD_DLL
	#else 
		#define DM_API
	#endif // DM_DMNAMIC_LINK
#else
	#error DM only supports windows
#endif // DM_PLATFORM_WINDOWS

#define DM_ENABLE_ASSERT
#ifdef DM_ENABLE_ASSERT
	#define DM_ASSERT(x,fmt,...)\
			{\
				if(!(x))\
				{\
					std::string str("Assertion Failed.File:{}---Line:{}.");\
					str+=fmt;\
					LOG_ERROR(str.c_str(),__FILE__,__LINE__,__VA_ARGS__);\
					__debugbreak();\
				}\
			}
	
	#define DM_CORE_ASSERT(x,fmt,...)\
			{\
				if(!(x))\
				{\
					std::string str("Assertion Failed.File:{}---Line:{}.");\
					str+=fmt;\
					LOG_CORE_ERROR(str.c_str(),__FILE__,__LINE__,__VA_ARGS__);\
					__debugbreak();\
				}\
			}
#else
	#define DM_ASSERT(x,...)
	#define DM_CORE_ASSERT(x,fmt,...)
#endif // DM_ENABLE_ASSERT






