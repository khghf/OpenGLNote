#pragma once
#include<Reflect/GeneratedHppIncludes.h>
class AAA_GameSetting_Operator;
namespace DM
{
	class GameSetting;
	DEC_TO_JSON(GameSetting)
	DEC_FROM_JSON(GameSetting)
}
#undef REFLECT_BODY_8
#define REFLECT_BODY_8()\
friend class AAA_GameSetting_Operator;\
typedef GameSetting ThisClass;\
typedef GInfo Super;\
public:\
Reflect_API static ::reflect::RClass*RClassInst();\
virtual std::string GetTypeName ()const override{return TypeName;}\
static constexpr  char* TypeName =TOSTR(GameSetting);\
private:\
