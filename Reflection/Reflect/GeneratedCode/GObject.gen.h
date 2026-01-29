#pragma once
#include<Reflect/GeneratedHppIncludes.h>
class AAA_GObject_Operator;
namespace DM
{
	class GObject;
	DEC_TO_JSON(GObject)
	DEC_FROM_JSON(GObject)
}
#undef REFLECT_BODY_12
#define REFLECT_BODY_12()\
friend class AAA_GObject_Operator;\
typedef GObject ThisClass;\
public:\
Reflect_API static ::reflect::RClass*RClassInst();\
virtual std::string GetTypeName ()const{return TypeName;}\
static constexpr  char* TypeName =TOSTR(GObject);\
private:\
