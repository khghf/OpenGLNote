#pragma once
#include<Reflect/GeneratedHppIncludes.h>
class AAA_GWorld_Operator;
namespace DM
{
	class GWorld;
	DEC_TO_JSON(GWorld)
	DEC_FROM_JSON(GWorld)
}
#undef REFLECT_BODY_9
#define REFLECT_BODY_9()\
friend class AAA_GWorld_Operator;\
typedef GWorld ThisClass;\
typedef GObject Super;\
public:\
Reflect_API static ::reflect::RClass*RClassInst();\
virtual std::string GetTypeName ()const override{return TypeName;}\
static constexpr  char* TypeName =TOSTR(GWorld);\
private:\
