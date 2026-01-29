#include<Reflect/GeneratedCppIncludes.h>
#include"../../DM/Src\FrameWork\GPlayer.h"
class AAA_GPlayer_Operator
{
public:
	ConstructRClass(GPlayer,DM)
	static void ToJson(::nlohmann::json&j,const void*obj)
	{
		const DM::GPlayer*ptr=static_cast<const DM::GPlayer*>(obj);
	}
	static void FromJson(const ::nlohmann::json&j,void*obj)
	{
		DM::GPlayer*ptr=new DM::GPlayer();
		obj=ptr;
	}
};
::reflect::RClass*DM::GPlayer::RClassInst()
{
	return AAA_GPlayer_Operator::ConstructRClass_GPlayer(); 
}
namespace DM
{
	DEF_TO_JSON(GPlayer)
	DEF_FROM_JSON(GPlayer)
}
extern reflect::RClass*AAA_Construct_RClass_GCharacter();
reflect::RClass*AAA_Construct_RClass_GPlayer()
{
	return AAA_GPlayer_Operator::ConstructRClass_GPlayer(); 
}
	void ToJson(::nlohmann::json&j,const void*obj)
{
	AAA_GPlayer_Operator::ToJson(j,obj);
}
	void*FromJson(const ::nlohmann::json&j,void*obj)
{
	AAA_GPlayer_Operator::FromJson(j,obj);
}
struct AAA_Construct_GPlayer_Statics
{
	static RClassConstructor SuperClass_Constructor[];
	static RClassConstructor RClass_GPlayer_Constructor;
	const static uint32_t SuperClassNum;
	const static uint32_t FunctionNum;
	const static uint32_t PropertyNum;
	const static _TO_JSON_ ToJson;
	const static _FROM_JSON_ FromJson;
};
RClassConstructor AAA_Construct_GPlayer_Statics::SuperClass_Constructor[]=
{
	AAA_Construct_RClass_GCharacter,
};
RClassConstructor AAA_Construct_GPlayer_Statics::RClass_GPlayer_Constructor = AAA_Construct_RClass_GPlayer;
const uint32_t AAA_Construct_GPlayer_Statics::SuperClassNum = ARRAY_COUNT(AAA_Construct_GPlayer_Statics::SuperClass_Constructor);
const uint32_t AAA_Construct_GPlayer_Statics::FunctionNum = 0;
const uint32_t AAA_Construct_GPlayer_Statics::PropertyNum = 0;
const _TO_JSON_ AAA_Construct_GPlayer_Statics::ToJson=ToJson;
const _FROM_JSON_ AAA_Construct_GPlayer_Statics::FromJson=FromJson;
static RegistrationInfo Collector_GPlayer=
{
	AAA_Construct_GPlayer_Statics::SuperClass_Constructor,
	AAA_Construct_GPlayer_Statics::RClass_GPlayer_Constructor,
	nullptr,
	nullptr,
	AAA_Construct_GPlayer_Statics::SuperClassNum,
	AAA_Construct_GPlayer_Statics::FunctionNum,
	AAA_Construct_GPlayer_Statics::PropertyNum
};
static CollectRegistrationInfo Register_GPlayer(Collector_GPlayer); 
