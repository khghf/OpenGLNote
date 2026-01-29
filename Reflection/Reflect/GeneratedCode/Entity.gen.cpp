#include<Reflect/GeneratedCppIncludes.h>
#include"../../DM/Src\FrameWork\GActor.h"
class AAA_Entity_Operator
{
public:
	ConstructRClass(GActor,DM)
	ConstructRProperty(M__name,GActor,DM)
	static void ToJson(::nlohmann::json&j,const void*obj)
	{
		const DM::GActor*ptr=static_cast<const DM::GActor*>(obj);
		j[TOSTR(M__name)]=ptr->M__name;
	}
	static void FromJson(const ::nlohmann::json&j,void*obj);
	{
		DM::GActor*ptr=new DM::GActor()
		ptr->M__name=j[TOSTR(M__name)].get<std::string>();
	}
};
::reflect::RClass*DM::GActor::RClassInst()
{
	return AAA_Entity_Operator::ConstructRClass_Entity(); 
}
namespace DM
{
	void to_json(::nlohmann::json&j,const GActor&obj)
	{
		obj.to_json(j);
	}
	DEF_TO_JSON(GActor)
	void from_json(const ::nlohmann::json&j,GActor&obj)
	{
		obj.from_json(j);
	}
	DEF_FROM_JSON(GActor)
}
extern reflect::RClass*AAA_Construct_RClass_GObject();
reflect::RClass*AAA_Construct_RClass_Entity()
{
	return AAA_Entity_Operator::ConstructRClass_Entity(); 
}
reflect::RProperty*AAA_Construct_RProperty_M__name()
{
	return AAA_Entity_Operator::ConstructRProperty_M__name();
}
	void ToJson(::nlohmann::json&j,const void*obj)
{
	AAA_Entity_Operator::ToJson(j,obj);
}
	void*FromJson(const ::nlohmann::json&j,void*obj)
{
	AAA_Entity_Operator::FromJson(j,obj);
}
struct AAA_Construct_Entity_Statics
{
	static RClassConstructor SuperClass_Constructor[];
	static RClassConstructor RClass_Entity_Constructor;
	static RPropertyConstructor RProperty_Entity_Constructor[];
	const static uint32_t SuperClassNum;
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
	const static _TO_JSON_ ToJson;
	const static _FROM_JSON_ FromJson
};
RClassConstructor AAA_Construct_Entity_Statics::SuperClass_Constructor[]=
{
	AAA_Construct_RClass_GObject,
};
RClassConstructor AAA_Construct_Entity_Statics::RClass_Entity_Constructor = AAA_Construct_RClass_Entity;
RPropertyConstructor AAA_Construct_Entity_Statics::RProperty_Entity_Constructor[]=
{
	AAA_Construct_RProperty_M__name,
};
const uint32_t AAA_Construct_Entity_Statics::SuperClassNum = ARRAY_COUNT(AAA_Construct_Entity_Statics::SuperClass_Constructor);
const uint32_t AAA_Construct_Entity_Statics::FunctionNum = 0;
const uint32_t AAA_Construct_Entity_Statics::PropertyNum = ARRAY_COUNT(AAA_Construct_Entity_Statics::RProperty_Entity_Constructor);
_TO_JSON_AAA_Construct_Entity_Statics::ToJson=ToJson;
_FROM_JSON_ AAA_Construct_Entity_Statics::FromJson=FromJson;
static RegistrationInfo Collector_Entity=
{
	AAA_Construct_Entity_Statics::SuperClass_Constructor,
	AAA_Construct_Entity_Statics::RClass_Entity_Constructor,
	nullptr,
	AAA_Construct_Entity_Statics::RProperty_Entity_Constructor,
	AAA_Construct_Entity_Statics::SuperClassNum,
	AAA_Construct_Entity_Statics::FunctionNum,
	AAA_Construct_Entity_Statics::PropertyNum
};
static CollectRegistrationInfo Register_Entity(Collector_Entity); 
