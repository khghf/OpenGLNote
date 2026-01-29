#include<Reflect/GeneratedCppIncludes.h>
#include"../../DM/Src\FrameWork\GController.h"
class AAA_GController_Operator
{
public:
	ConstructRClass(GController,DM)
	static void ToJson(::nlohmann::json&j,const void*obj)
	{
		const DM::GController*ptr=static_cast<const DM::GController*>(obj);
	}
	static void FromJson(const ::nlohmann::json&j,void*obj)
	{
		DM::GController*ptr=new DM::GController();
		obj=ptr;
	}
};
::reflect::RClass*DM::GController::RClassInst()
{
	return AAA_GController_Operator::ConstructRClass_GController(); 
}
namespace DM
{
	DEF_TO_JSON(GController)
	DEF_FROM_JSON(GController)
}
extern reflect::RClass*AAA_Construct_RClass_GActor();
reflect::RClass*AAA_Construct_RClass_GController()
{
	return AAA_GController_Operator::ConstructRClass_GController(); 
}
	void ToJson(::nlohmann::json&j,const void*obj)
{
	AAA_GController_Operator::ToJson(j,obj);
}
	void*FromJson(const ::nlohmann::json&j,void*obj)
{
	AAA_GController_Operator::FromJson(j,obj);
}
struct AAA_Construct_GController_Statics
{
	static RClassConstructor SuperClass_Constructor[];
	static RClassConstructor RClass_GController_Constructor;
	const static uint32_t SuperClassNum;
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
	const static _TO_JSON_ ToJson;
	const static _FROM_JSON_ FromJson;
};
RClassConstructor AAA_Construct_GController_Statics::SuperClass_Constructor[]=
{
	AAA_Construct_RClass_GActor,
};
RClassConstructor AAA_Construct_GController_Statics::RClass_GController_Constructor = AAA_Construct_RClass_GController;
const uint32_t AAA_Construct_GController_Statics::SuperClassNum = ARRAY_COUNT(AAA_Construct_GController_Statics::SuperClass_Constructor);
const uint32_t AAA_Construct_GController_Statics::FunctionNum = 0;
const uint32_t AAA_Construct_GController_Statics::PropertyNum = 0;
const _TO_JSON_ AAA_Construct_GController_Statics::ToJson=ToJson;
const _FROM_JSON_ AAA_Construct_GController_Statics::FromJson=FromJson;
static RegistrationInfo Collector_GController=
{
	AAA_Construct_GController_Statics::SuperClass_Constructor,
	AAA_Construct_GController_Statics::RClass_GController_Constructor,
	nullptr,
	nullptr,
	AAA_Construct_GController_Statics::SuperClassNum,
	AAA_Construct_GController_Statics::FunctionNum,
	AAA_Construct_GController_Statics::PropertyNum
};
static CollectRegistrationInfo Register_GController(Collector_GController); 
