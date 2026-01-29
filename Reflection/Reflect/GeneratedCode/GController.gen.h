#pragma once
#include<Reflect/GeneratedHppIncludes.h>
class AAA_GController_Operator;
namespace DM
{
	class GController;
	DEC_TO_JSON(GController)
	DEC_FROM_JSON(GController)
}
#undef REFLECT_BODY_8
#define REFLECT_BODY_8()\
friend class AAA_GController_Operator;\
typedef GController ThisClass;\
typedef GActor Super;\
public:\
Reflect_API static ::reflect::RClass*RClassInst();\
virtual std::string GetTypeName ()const override{return TypeName;}\
static constexpr  char* TypeName =TOSTR(GController);\
private:\
