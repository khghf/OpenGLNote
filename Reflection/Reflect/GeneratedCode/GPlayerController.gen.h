#pragma once
#include<Reflect/GeneratedHppIncludes.h>
class AAA_GPlayerController_Operator;
namespace DM
{
	class GPlayerController;
	DEC_TO_JSON(GPlayerController)
	DEC_FROM_JSON(GPlayerController)
}
#undef REFLECT_BODY_8
#define REFLECT_BODY_8()\
friend class AAA_GPlayerController_Operator;\
typedef GPlayerController ThisClass;\
typedef GController Super;\
public:\
Reflect_API static ::reflect::RClass*RClassInst();\
virtual std::string GetTypeName ()const override{return TypeName;}\
static constexpr  char* TypeName =TOSTR(GPlayerController);\
private:\
