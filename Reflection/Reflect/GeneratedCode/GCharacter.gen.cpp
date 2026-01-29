#include<Reflect/GeneratedCppIncludes.h>
#include"../../DM/Src\FrameWork\GCharacter.h"
class AAA_GCharacter_Operator
{
public:
	ConstructRClass(GCharacter,DM)
	static void ToJson(::nlohmann::json&j,const void*obj)
	{
		const DM::GCharacter*ptr=static_cast<const DM::GCharacter*>(obj);
	}
	static void FromJson(const ::nlohmann::json&j,void*obj)
	{
		DM::GCharacter*ptr=new DM::GCharacter();
		obj=ptr;
	}
};
::reflect::RClass*DM::GCharacter::RClassInst()
{
	return AAA_GCharacter_Operator::ConstructRClass_GCharacter(); 
}
namespace DM
{
	DEF_TO_JSON(GCharacter)
	DEF_FROM_JSON(GCharacter)
}
extern reflect::RClass*AAA_Construct_RClass_GActor();
reflect::RClass*AAA_Construct_RClass_GCharacter()
{
	return AAA_GCharacter_Operator::ConstructRClass_GCharacter(); 
}
	void ToJson(::nlohmann::json&j,const void*obj)
{
	AAA_GCharacter_Operator::ToJson(j,obj);
}
	void*FromJson(const ::nlohmann::json&j,void*obj)
{
	AAA_GCharacter_Operator::FromJson(j,obj);
}
struct AAA_Construct_GCharacter_Statics
{
	static RClassConstructor SuperClass_Constructor[];
	static RClassConstructor RClass_GCharacter_Constructor;
	const static uint32_t SuperClassNum;
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
	const static _TO_JSON_ ToJson;
	const static _FROM_JSON_ FromJson;
};
RClassConstructor AAA_Construct_GCharacter_Statics::SuperClass_Constructor[]=
{
	AAA_Construct_RClass_GActor,
};
RClassConstructor AAA_Construct_GCharacter_Statics::RClass_GCharacter_Constructor = AAA_Construct_RClass_GCharacter;
const uint32_t AAA_Construct_GCharacter_Statics::SuperClassNum = ARRAY_COUNT(AAA_Construct_GCharacter_Statics::SuperClass_Constructor);
const uint32_t AAA_Construct_GCharacter_Statics::FunctionNum = 0;
const uint32_t AAA_Construct_GCharacter_Statics::PropertyNum = 0;
const _TO_JSON_ AAA_Construct_GCharacter_Statics::ToJson=ToJson;
const _FROM_JSON_ AAA_Construct_GCharacter_Statics::FromJson=FromJson;
static RegistrationInfo Collector_GCharacter=
{
	AAA_Construct_GCharacter_Statics::SuperClass_Constructor,
	AAA_Construct_GCharacter_Statics::RClass_GCharacter_Constructor,
	nullptr,
	nullptr,
	AAA_Construct_GCharacter_Statics::SuperClassNum,
	AAA_Construct_GCharacter_Statics::FunctionNum,
	AAA_Construct_GCharacter_Statics::PropertyNum
};
static CollectRegistrationInfo Register_GCharacter(Collector_GCharacter); 
