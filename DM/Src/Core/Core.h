#pragma once
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
	#define DM_ASSERT(x,...){if(!(x)){LOG_ERROR("Assertion Failed:{}",__VA_ARGS__);__debugbreak();}}
	#define DM_CORE_ASSERT(x,...){if(!(x)){LOG_Core_ERROR("Assertion Failed:{}",__VA_ARGS__);__debugbreak();}}
#else
	#define DM_ASSERT(x,...)
	#define DM_CORE_ASSERT(x,...)
#endif // DM_ENABLE_ASSERT
