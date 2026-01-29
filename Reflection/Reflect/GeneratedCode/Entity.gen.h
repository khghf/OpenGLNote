#pragma once
#include<Reflect/GeneratedHppIncludes.h>
class AAA_Entity_Operator;
namespace DM
{
	class GActor;
	DEC_TO_JSON(GActor)
	DEC_FROM_JSON(GActor)
}
#undef REFLECT_BODY_11
#define REFLECT_BODY_11()\
friend class AAA_Entity_Operator;\
typedef Entity ThisClass;\
public:\
Reflect_API static ::reflect::RClass*RClassInst();\
virtual std::string GetTypeName ()const override{return TypeName;}\
static constexpr  char* TypeName =TOSTR(Entity);\
private:\
