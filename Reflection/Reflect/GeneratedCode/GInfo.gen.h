#pragma once
#include<Reflect/GeneratedHppIncludes.h>
class AAA_GInfo_Operator;
namespace DM
{
	class GInfo;
	DEC_TO_JSON(GInfo)
	DEC_FROM_JSON(GInfo)
}
#undef REFLECT_BODY_8
#define REFLECT_BODY_8()\
friend class AAA_GInfo_Operator;\
typedef GInfo ThisClass;\
typedef GObject Super;\
public:\
Reflect_API static ::reflect::RClass*RClassInst();\
virtual std::string GetTypeName ()const override{return TypeName;}\
static constexpr  char* TypeName =TOSTR(GInfo);\
private:\
