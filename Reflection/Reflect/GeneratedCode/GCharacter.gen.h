#pragma once
#include<Reflect/GeneratedHppIncludes.h>
class AAA_GCharacter_Operator;
namespace DM
{
	class GCharacter;
	DEC_TO_JSON(GCharacter)
	DEC_FROM_JSON(GCharacter)
}
#undef REFLECT_BODY_8
#define REFLECT_BODY_8()\
friend class AAA_GCharacter_Operator;\
typedef GCharacter ThisClass;\
typedef GActor Super;\
public:\
Reflect_API static ::reflect::RClass*RClassInst();\
virtual std::string GetTypeName ()const override{return TypeName;}\
static constexpr  char* TypeName =TOSTR(GCharacter);\
private:\
