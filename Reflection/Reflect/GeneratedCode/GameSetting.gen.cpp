#include<Reflect/GeneratedCppIncludes.h>
#include"../../DM/Src\FrameWork\GameSetting.h"
class AAA_GameSetting_Operator
{
public:
	ConstructRClass(GameSetting,DM)
	static void ToJson(::nlohmann::json&j,const void*obj)
	{
		const DM::GameSetting*ptr=static_cast<const DM::GameSetting*>(obj);
	}
	static void FromJson(const ::nlohmann::json&j,void*obj)
	{
		DM::GameSetting*ptr=new DM::GameSetting();
		obj=ptr;
	}
};
::reflect::RClass*DM::GameSetting::RClassInst()
{
	return AAA_GameSetting_Operator::ConstructRClass_GameSetting(); 
}
namespace DM
{
	DEF_TO_JSON(GameSetting)
	DEF_FROM_JSON(GameSetting)
}
extern reflect::RClass*AAA_Construct_RClass_GInfo();
reflect::RClass*AAA_Construct_RClass_GameSetting()
{
	return AAA_GameSetting_Operator::ConstructRClass_GameSetting(); 
}
	void ToJson(::nlohmann::json&j,const void*obj)
{
	AAA_GameSetting_Operator::ToJson(j,obj);
}
	void*FromJson(const ::nlohmann::json&j,void*obj)
{
	AAA_GameSetting_Operator::FromJson(j,obj);
}
struct AAA_Construct_GameSetting_Statics
{
	static RClassConstructor SuperClass_Constructor[];
	static RClassConstructor RClass_GameSetting_Constructor;
	const static uint32_t SuperClassNum;
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
	const static _TO_JSON_ ToJson;
	const static _FROM_JSON_ FromJson;
};
RClassConstructor AAA_Construct_GameSetting_Statics::SuperClass_Constructor[]=
{
	AAA_Construct_RClass_GInfo,
};
RClassConstructor AAA_Construct_GameSetting_Statics::RClass_GameSetting_Constructor = AAA_Construct_RClass_GameSetting;
const uint32_t AAA_Construct_GameSetting_Statics::SuperClassNum = ARRAY_COUNT(AAA_Construct_GameSetting_Statics::SuperClass_Constructor);
const uint32_t AAA_Construct_GameSetting_Statics::FunctionNum = 0;
const uint32_t AAA_Construct_GameSetting_Statics::PropertyNum = 0;
const _TO_JSON_ AAA_Construct_GameSetting_Statics::ToJson=ToJson;
const _FROM_JSON_ AAA_Construct_GameSetting_Statics::FromJson=FromJson;
static RegistrationInfo Collector_GameSetting=
{
	AAA_Construct_GameSetting_Statics::SuperClass_Constructor,
	AAA_Construct_GameSetting_Statics::RClass_GameSetting_Constructor,
	nullptr,
	nullptr,
	AAA_Construct_GameSetting_Statics::SuperClassNum,
	AAA_Construct_GameSetting_Statics::FunctionNum,
	AAA_Construct_GameSetting_Statics::PropertyNum
};
static CollectRegistrationInfo Register_GameSetting(Collector_GameSetting); 
