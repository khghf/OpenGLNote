#include<Reflect/GeneratedCppIncludes.h>
#include"../../DM/Src\FrameWork\WorldSetting.h"
class AAA_WorldSetting_Operator
{
public:
	ConstructRClass(WorldSetting,DM)
	static void ToJson(::nlohmann::json&j,const void*obj)
	{
		const DM::WorldSetting*ptr=static_cast<const DM::WorldSetting*>(obj);
	}
	static void FromJson(const ::nlohmann::json&j,void*obj)
	{
		DM::WorldSetting*ptr=new DM::WorldSetting();
		obj=ptr;
	}
};
::reflect::RClass*DM::WorldSetting::RClassInst()
{
	return AAA_WorldSetting_Operator::ConstructRClass_WorldSetting(); 
}
namespace DM
{
	DEF_TO_JSON(WorldSetting)
	DEF_FROM_JSON(WorldSetting)
}
extern reflect::RClass*AAA_Construct_RClass_GInfo();
reflect::RClass*AAA_Construct_RClass_WorldSetting()
{
	return AAA_WorldSetting_Operator::ConstructRClass_WorldSetting(); 
}
	void ToJson(::nlohmann::json&j,const void*obj)
{
	AAA_WorldSetting_Operator::ToJson(j,obj);
}
	void*FromJson(const ::nlohmann::json&j,void*obj)
{
	AAA_WorldSetting_Operator::FromJson(j,obj);
}
struct AAA_Construct_WorldSetting_Statics
{
	static RClassConstructor SuperClass_Constructor[];
	static RClassConstructor RClass_WorldSetting_Constructor;
	const static uint32_t SuperClassNum;
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
	const static _TO_JSON_ ToJson;
	const static _FROM_JSON_ FromJson;
};
RClassConstructor AAA_Construct_WorldSetting_Statics::SuperClass_Constructor[]=
{
	AAA_Construct_RClass_GInfo,
};
RClassConstructor AAA_Construct_WorldSetting_Statics::RClass_WorldSetting_Constructor = AAA_Construct_RClass_WorldSetting;
const uint32_t AAA_Construct_WorldSetting_Statics::SuperClassNum = ARRAY_COUNT(AAA_Construct_WorldSetting_Statics::SuperClass_Constructor);
const uint32_t AAA_Construct_WorldSetting_Statics::FunctionNum = 0;
const uint32_t AAA_Construct_WorldSetting_Statics::PropertyNum = 0;
const _TO_JSON_ AAA_Construct_WorldSetting_Statics::ToJson=ToJson;
const _FROM_JSON_ AAA_Construct_WorldSetting_Statics::FromJson=FromJson;
static RegistrationInfo Collector_WorldSetting=
{
	AAA_Construct_WorldSetting_Statics::SuperClass_Constructor,
	AAA_Construct_WorldSetting_Statics::RClass_WorldSetting_Constructor,
	nullptr,
	nullptr,
	AAA_Construct_WorldSetting_Statics::SuperClassNum,
	AAA_Construct_WorldSetting_Statics::FunctionNum,
	AAA_Construct_WorldSetting_Statics::PropertyNum
};
static CollectRegistrationInfo Register_WorldSetting(Collector_WorldSetting); 
