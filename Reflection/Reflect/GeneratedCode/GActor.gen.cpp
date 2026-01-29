#include<Reflect/GeneratedCppIncludes.h>
#include"../../DM/Src\FrameWork\GActor.h"
class AAA_GActor_Operator
{
public:
	ConstructRClass(GActor,DM)
	ConstructRProperty(M__name,GActor,DM)
	static void ToJson(::nlohmann::json&j,const void*obj)
	{
		const DM::GActor*ptr=static_cast<const DM::GActor*>(obj);
		j[TOSTR(M__name)]=ptr->M__name;
	}
	static void FromJson(const ::nlohmann::json&j,void*obj)
	{
		DM::GActor*ptr=new DM::GActor();
		ptr->M__name=j[TOSTR(M__name)].get<std::string>();
		obj=ptr;
	}
};
::reflect::RClass*DM::GActor::RClassInst()
{
	return AAA_GActor_Operator::ConstructRClass_GActor(); 
}
namespace DM
{
	DEF_TO_JSON(GActor)
	DEF_FROM_JSON(GActor)
}
extern reflect::RClass*AAA_Construct_RClass_GObject();
reflect::RClass*AAA_Construct_RClass_GActor()
{
	return AAA_GActor_Operator::ConstructRClass_GActor(); 
}
reflect::RProperty*AAA_Construct_RProperty_M__name()
{
	return AAA_GActor_Operator::ConstructRProperty_M__name();
}
	void ToJson(::nlohmann::json&j,const void*obj)
{
	AAA_GActor_Operator::ToJson(j,obj);
}
	void*FromJson(const ::nlohmann::json&j,void*obj)
{
	AAA_GActor_Operator::FromJson(j,obj);
}
struct AAA_Construct_GActor_Statics
{
	static RClassConstructor SuperClass_Constructor[];
	static RClassConstructor RClass_GActor_Constructor;
	static RPropertyConstructor RProperty_GActor_Constructor[];
	const static uint32_t SuperClassNum;
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
	const static _TO_JSON_ ToJson;
	const static _FROM_JSON_ FromJson;
};
RClassConstructor AAA_Construct_GActor_Statics::SuperClass_Constructor[]=
{
	AAA_Construct_RClass_GObject,
};
RClassConstructor AAA_Construct_GActor_Statics::RClass_GActor_Constructor = AAA_Construct_RClass_GActor;
RPropertyConstructor AAA_Construct_GActor_Statics::RProperty_GActor_Constructor[]=
{
	AAA_Construct_RProperty_M__name,
};
const uint32_t AAA_Construct_GActor_Statics::SuperClassNum = ARRAY_COUNT(AAA_Construct_GActor_Statics::SuperClass_Constructor);
const uint32_t AAA_Construct_GActor_Statics::FunctionNum = 0;
const uint32_t AAA_Construct_GActor_Statics::PropertyNum = ARRAY_COUNT(AAA_Construct_GActor_Statics::RProperty_GActor_Constructor);
const _TO_JSON_ AAA_Construct_GActor_Statics::ToJson=ToJson;
const _FROM_JSON_ AAA_Construct_GActor_Statics::FromJson=FromJson;
static RegistrationInfo Collector_GActor=
{
	AAA_Construct_GActor_Statics::SuperClass_Constructor,
	AAA_Construct_GActor_Statics::RClass_GActor_Constructor,
	nullptr,
	AAA_Construct_GActor_Statics::RProperty_GActor_Constructor,
	AAA_Construct_GActor_Statics::SuperClassNum,
	AAA_Construct_GActor_Statics::FunctionNum,
	AAA_Construct_GActor_Statics::PropertyNum
};
static CollectRegistrationInfo Register_GActor(Collector_GActor); 
