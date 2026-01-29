#include<Reflect/GeneratedCppIncludes.h>
#include"../../DM/Src\FrameWork\GInfo.h"
class AAA_GInfo_Operator
{
public:
	ConstructRClass(GInfo,DM)
	static void ToJson(::nlohmann::json&j,const void*obj)
	{
		const DM::GInfo*ptr=static_cast<const DM::GInfo*>(obj);
	}
	static void FromJson(const ::nlohmann::json&j,void*obj)
	{
		DM::GInfo*ptr=new DM::GInfo();
		obj=ptr;
	}
};
::reflect::RClass*DM::GInfo::RClassInst()
{
	return AAA_GInfo_Operator::ConstructRClass_GInfo(); 
}
namespace DM
{
	DEF_TO_JSON(GInfo)
	DEF_FROM_JSON(GInfo)
}
extern reflect::RClass*AAA_Construct_RClass_GObject();
reflect::RClass*AAA_Construct_RClass_GInfo()
{
	return AAA_GInfo_Operator::ConstructRClass_GInfo(); 
}
	void ToJson(::nlohmann::json&j,const void*obj)
{
	AAA_GInfo_Operator::ToJson(j,obj);
}
	void*FromJson(const ::nlohmann::json&j,void*obj)
{
	AAA_GInfo_Operator::FromJson(j,obj);
}
struct AAA_Construct_GInfo_Statics
{
	static RClassConstructor SuperClass_Constructor[];
	static RClassConstructor RClass_GInfo_Constructor;
	const static uint32_t SuperClassNum;
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
	const static _TO_JSON_ ToJson;
	const static _FROM_JSON_ FromJson;
};
RClassConstructor AAA_Construct_GInfo_Statics::SuperClass_Constructor[]=
{
	AAA_Construct_RClass_GObject,
};
RClassConstructor AAA_Construct_GInfo_Statics::RClass_GInfo_Constructor = AAA_Construct_RClass_GInfo;
const uint32_t AAA_Construct_GInfo_Statics::SuperClassNum = ARRAY_COUNT(AAA_Construct_GInfo_Statics::SuperClass_Constructor);
const uint32_t AAA_Construct_GInfo_Statics::FunctionNum = 0;
const uint32_t AAA_Construct_GInfo_Statics::PropertyNum = 0;
const _TO_JSON_ AAA_Construct_GInfo_Statics::ToJson=ToJson;
const _FROM_JSON_ AAA_Construct_GInfo_Statics::FromJson=FromJson;
static RegistrationInfo Collector_GInfo=
{
	AAA_Construct_GInfo_Statics::SuperClass_Constructor,
	AAA_Construct_GInfo_Statics::RClass_GInfo_Constructor,
	nullptr,
	nullptr,
	AAA_Construct_GInfo_Statics::SuperClassNum,
	AAA_Construct_GInfo_Statics::FunctionNum,
	AAA_Construct_GInfo_Statics::PropertyNum
};
static CollectRegistrationInfo Register_GInfo(Collector_GInfo); 
