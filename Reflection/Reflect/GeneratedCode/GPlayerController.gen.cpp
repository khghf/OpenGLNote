#include<Reflect/GeneratedCppIncludes.h>
#include"../../DM/Src\FrameWork\GPlayerController.h"
class AAA_GPlayerController_Operator
{
public:
	ConstructRClass(GPlayerController,DM)
	static void ToJson(::nlohmann::json&j,const void*obj)
	{
		const DM::GPlayerController*ptr=static_cast<const DM::GPlayerController*>(obj);
	}
	static void FromJson(const ::nlohmann::json&j,void*obj)
	{
		DM::GPlayerController*ptr=new DM::GPlayerController();
		obj=ptr;
	}
};
::reflect::RClass*DM::GPlayerController::RClassInst()
{
	return AAA_GPlayerController_Operator::ConstructRClass_GPlayerController(); 
}
namespace DM
{
	DEF_TO_JSON(GPlayerController)
	DEF_FROM_JSON(GPlayerController)
}
extern reflect::RClass*AAA_Construct_RClass_GController();
reflect::RClass*AAA_Construct_RClass_GPlayerController()
{
	return AAA_GPlayerController_Operator::ConstructRClass_GPlayerController(); 
}
	void ToJson(::nlohmann::json&j,const void*obj)
{
	AAA_GPlayerController_Operator::ToJson(j,obj);
}
	void*FromJson(const ::nlohmann::json&j,void*obj)
{
	AAA_GPlayerController_Operator::FromJson(j,obj);
}
struct AAA_Construct_GPlayerController_Statics
{
	static RClassConstructor SuperClass_Constructor[];
	static RClassConstructor RClass_GPlayerController_Constructor;
	const static uint32_t SuperClassNum;
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
	const static _TO_JSON_ ToJson;
	const static _FROM_JSON_ FromJson;
};
RClassConstructor AAA_Construct_GPlayerController_Statics::SuperClass_Constructor[]=
{
	AAA_Construct_RClass_GController,
};
RClassConstructor AAA_Construct_GPlayerController_Statics::RClass_GPlayerController_Constructor = AAA_Construct_RClass_GPlayerController;
const uint32_t AAA_Construct_GPlayerController_Statics::SuperClassNum = ARRAY_COUNT(AAA_Construct_GPlayerController_Statics::SuperClass_Constructor);
const uint32_t AAA_Construct_GPlayerController_Statics::FunctionNum = 0;
const uint32_t AAA_Construct_GPlayerController_Statics::PropertyNum = 0;
const _TO_JSON_ AAA_Construct_GPlayerController_Statics::ToJson=ToJson;
const _FROM_JSON_ AAA_Construct_GPlayerController_Statics::FromJson=FromJson;
static RegistrationInfo Collector_GPlayerController=
{
	AAA_Construct_GPlayerController_Statics::SuperClass_Constructor,
	AAA_Construct_GPlayerController_Statics::RClass_GPlayerController_Constructor,
	nullptr,
	nullptr,
	AAA_Construct_GPlayerController_Statics::SuperClassNum,
	AAA_Construct_GPlayerController_Statics::FunctionNum,
	AAA_Construct_GPlayerController_Statics::PropertyNum
};
static CollectRegistrationInfo Register_GPlayerController(Collector_GPlayerController); 
