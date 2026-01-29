#include<Reflect/GeneratedCppIncludes.h>
#include"../../DM/Src\FrameWork\GWorld.h"
class AAA_GWorld_Operator
{
public:
	ConstructRClass(GWorld,DM)
	ConstructRProperty(m_Name,GWorld,DM)
	static void ToJson(::nlohmann::json&j,const void*obj)
	{
		const DM::GWorld*ptr=static_cast<const DM::GWorld*>(obj);
		j[TOSTR(m_Name)]=ptr->m_Name;
	}
	static void FromJson(const ::nlohmann::json&j,void*obj)
	{
		DM::GWorld*ptr=new DM::GWorld();
		ptr->m_Name=j[TOSTR(m_Name)].get<std::string>();
		obj=ptr;
	}
};
::reflect::RClass*DM::GWorld::RClassInst()
{
	return AAA_GWorld_Operator::ConstructRClass_GWorld(); 
}
namespace DM
{
	DEF_TO_JSON(GWorld)
	DEF_FROM_JSON(GWorld)
}
extern reflect::RClass*AAA_Construct_RClass_GObject();
reflect::RClass*AAA_Construct_RClass_GWorld()
{
	return AAA_GWorld_Operator::ConstructRClass_GWorld(); 
}
reflect::RProperty*AAA_Construct_RProperty_m_Name()
{
	return AAA_GWorld_Operator::ConstructRProperty_m_Name();
}
	void ToJson(::nlohmann::json&j,const void*obj)
{
	AAA_GWorld_Operator::ToJson(j,obj);
}
	void*FromJson(const ::nlohmann::json&j,void*obj)
{
	AAA_GWorld_Operator::FromJson(j,obj);
}
struct AAA_Construct_GWorld_Statics
{
	static RClassConstructor SuperClass_Constructor[];
	static RClassConstructor RClass_GWorld_Constructor;
	static RPropertyConstructor RProperty_GWorld_Constructor[];
	const static uint32_t SuperClassNum;
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
	const static _TO_JSON_ ToJson;
	const static _FROM_JSON_ FromJson;
};
RClassConstructor AAA_Construct_GWorld_Statics::SuperClass_Constructor[]=
{
	AAA_Construct_RClass_GObject,
};
RClassConstructor AAA_Construct_GWorld_Statics::RClass_GWorld_Constructor = AAA_Construct_RClass_GWorld;
RPropertyConstructor AAA_Construct_GWorld_Statics::RProperty_GWorld_Constructor[]=
{
	AAA_Construct_RProperty_m_Name,
};
const uint32_t AAA_Construct_GWorld_Statics::SuperClassNum = ARRAY_COUNT(AAA_Construct_GWorld_Statics::SuperClass_Constructor);
const uint32_t AAA_Construct_GWorld_Statics::FunctionNum = 0;
const uint32_t AAA_Construct_GWorld_Statics::PropertyNum = ARRAY_COUNT(AAA_Construct_GWorld_Statics::RProperty_GWorld_Constructor);
const _TO_JSON_ AAA_Construct_GWorld_Statics::ToJson=ToJson;
const _FROM_JSON_ AAA_Construct_GWorld_Statics::FromJson=FromJson;
static RegistrationInfo Collector_GWorld=
{
	AAA_Construct_GWorld_Statics::SuperClass_Constructor,
	AAA_Construct_GWorld_Statics::RClass_GWorld_Constructor,
	nullptr,
	AAA_Construct_GWorld_Statics::RProperty_GWorld_Constructor,
	AAA_Construct_GWorld_Statics::SuperClassNum,
	AAA_Construct_GWorld_Statics::FunctionNum,
	AAA_Construct_GWorld_Statics::PropertyNum
};
static CollectRegistrationInfo Register_GWorld(Collector_GWorld); 
