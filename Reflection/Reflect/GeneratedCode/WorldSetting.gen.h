#pragma once
#include<Reflect/GeneratedHppIncludes.h>
class AAA_WorldSetting_Operator;
namespace DM
{
	class WorldSetting;
	DEC_TO_JSON(WorldSetting)
	DEC_FROM_JSON(WorldSetting)
}
#undef REFLECT_BODY_8
#define REFLECT_BODY_8()\
friend class AAA_WorldSetting_Operator;\
typedef WorldSetting ThisClass;\
typedef GInfo Super;\
public:\
Reflect_API static ::reflect::RClass*RClassInst();\
virtual std::string GetTypeName ()const override{return TypeName;}\
static constexpr  char* TypeName =TOSTR(WorldSetting);\
private:\
