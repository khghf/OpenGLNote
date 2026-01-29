#pragma once
#include<Reflect/GeneratedHppIncludes.h>
class AAA_GPlayer_Operator;
namespace DM
{
	class GPlayer;
	DEC_TO_JSON(GPlayer)
	DEC_FROM_JSON(GPlayer)
}
#undef REFLECT_BODY_8
#define REFLECT_BODY_8()\
friend class AAA_GPlayer_Operator;\
typedef GPlayer ThisClass;\
typedef GCharacter Super;\
public:\
Reflect_API static ::reflect::RClass*RClassInst();\
virtual std::string GetTypeName ()const override{return TypeName;}\
static constexpr  char* TypeName =TOSTR(GPlayer);\
private:\
