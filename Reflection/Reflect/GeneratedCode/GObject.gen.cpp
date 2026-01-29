#include<Reflect/GeneratedCppIncludes.h>
#include"../../DM/Src\FrameWork\GObject.h"
class AAA_GObject_Operator
{
public:
	ConstructRClass(GObject,DM)
	ConstructRProperty(bEnableUpdate,GObject,DM)
	ConstructRProperty(test1,GObject,DM)
	ConstructRProperty(test2,GObject,DM)
	ConstructRProperty(name,GObject,DM)
	ConstructRProperty(vec,GObject,DM)
	ConstructRProperty(vec2,GObject,DM)
	ConstructRProperty(map,GObject,DM)
	ConstructRProperty(bEnableUpdate2,GObject,DM)
	static void ToJson(::nlohmann::json&j,const void*obj)
	{
		const DM::GObject*ptr=static_cast<const DM::GObject*>(obj);
		j[TOSTR(bEnableUpdate)]=ptr->bEnableUpdate;
		j[TOSTR(test1)]=ptr->test1;
		j[TOSTR(test2)]=ptr->test2;
		j[TOSTR(name)]=ptr->name;
		j[TOSTR(vec)]=ptr->vec;
		j[TOSTR(vec2)]=ptr->vec2;
		j[TOSTR(map)]=ptr->map;
		j[TOSTR(bEnableUpdate2)]=ptr->bEnableUpdate2;
	}
	static void FromJson(const ::nlohmann::json&j,void*obj)
	{
		DM::GObject*ptr=new DM::GObject();
		ptr->bEnableUpdate=j[TOSTR(bEnableUpdate)].get<bool>();
		ptr->test1=j[TOSTR(test1)].get<int>();
		ptr->test2=j[TOSTR(test2)].get<int>();
		ptr->name=j[TOSTR(name)].get<std::string>();
		ptr->vec=j[TOSTR(vec)].get<std::vector<int>>();
		ptr->vec2=j[TOSTR(vec2)].get<std::vector<float>>();
		ptr->map=j[TOSTR(map)].get<std::map<float, int>>();
		ptr->bEnableUpdate2=j[TOSTR(bEnableUpdate2)].get<bool>();
		obj=ptr;
	}
};
::reflect::RClass*DM::GObject::RClassInst()
{
	return AAA_GObject_Operator::ConstructRClass_GObject(); 
}
namespace DM
{
	DEF_TO_JSON(GObject)
	DEF_FROM_JSON(GObject)
}
reflect::RClass*AAA_Construct_RClass_GObject()
{
	return AAA_GObject_Operator::ConstructRClass_GObject(); 
}
reflect::RProperty*AAA_Construct_RProperty_bEnableUpdate()
{
	return AAA_GObject_Operator::ConstructRProperty_bEnableUpdate();
}
reflect::RProperty*AAA_Construct_RProperty_test1()
{
	return AAA_GObject_Operator::ConstructRProperty_test1();
}
reflect::RProperty*AAA_Construct_RProperty_test2()
{
	return AAA_GObject_Operator::ConstructRProperty_test2();
}
reflect::RProperty*AAA_Construct_RProperty_name()
{
	return AAA_GObject_Operator::ConstructRProperty_name();
}
reflect::RProperty*AAA_Construct_RProperty_vec()
{
	return AAA_GObject_Operator::ConstructRProperty_vec();
}
reflect::RProperty*AAA_Construct_RProperty_vec2()
{
	return AAA_GObject_Operator::ConstructRProperty_vec2();
}
reflect::RProperty*AAA_Construct_RProperty_map()
{
	return AAA_GObject_Operator::ConstructRProperty_map();
}
reflect::RProperty*AAA_Construct_RProperty_bEnableUpdate2()
{
	return AAA_GObject_Operator::ConstructRProperty_bEnableUpdate2();
}
	void ToJson(::nlohmann::json&j,const void*obj)
{
	AAA_GObject_Operator::ToJson(j,obj);
}
	void*FromJson(const ::nlohmann::json&j,void*obj)
{
	AAA_GObject_Operator::FromJson(j,obj);
}
struct AAA_Construct_GObject_Statics
{
	static RClassConstructor RClass_GObject_Constructor;
	static RPropertyConstructor RProperty_GObject_Constructor[];
	const static uint32_t SuperClassNum;
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
	const static _TO_JSON_ ToJson;
	const static _FROM_JSON_ FromJson;
};
RClassConstructor AAA_Construct_GObject_Statics::RClass_GObject_Constructor = AAA_Construct_RClass_GObject;
RPropertyConstructor AAA_Construct_GObject_Statics::RProperty_GObject_Constructor[]=
{
	AAA_Construct_RProperty_bEnableUpdate,
	AAA_Construct_RProperty_test1,
	AAA_Construct_RProperty_test2,
	AAA_Construct_RProperty_name,
	AAA_Construct_RProperty_vec,
	AAA_Construct_RProperty_vec2,
	AAA_Construct_RProperty_map,
	AAA_Construct_RProperty_bEnableUpdate2,
};
const uint32_t AAA_Construct_GObject_Statics::SuperClassNum = 0;
const uint32_t AAA_Construct_GObject_Statics::FunctionNum = 0;
const uint32_t AAA_Construct_GObject_Statics::PropertyNum = ARRAY_COUNT(AAA_Construct_GObject_Statics::RProperty_GObject_Constructor);
const _TO_JSON_ AAA_Construct_GObject_Statics::ToJson=ToJson;
const _FROM_JSON_ AAA_Construct_GObject_Statics::FromJson=FromJson;
static RegistrationInfo Collector_GObject=
{
	nullptr,
	AAA_Construct_GObject_Statics::RClass_GObject_Constructor,
	nullptr,
	AAA_Construct_GObject_Statics::RProperty_GObject_Constructor,
	AAA_Construct_GObject_Statics::SuperClassNum,
	AAA_Construct_GObject_Statics::FunctionNum,
	AAA_Construct_GObject_Statics::PropertyNum
};
static CollectRegistrationInfo Register_GObject(Collector_GObject); 
