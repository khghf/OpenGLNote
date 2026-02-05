#include "DMPCH.h"
#include "GActor.h"
#include"GWorld.h"
#include<entt/entt.hpp>
#include"GComponent.h"
namespace DM
{


	GActor::GActor(entt::entity entityHandle, GWorld* context) :m_Handle(entityHandle), m_Context(context)
	{

	}


	void GActor::Update(float DeltaTime)
	{
		//Super::Updata(DeltaTime);
	}
	void GActor::Destroy()
	{
	}
	void GActor::OnDestroy()
	{
	}

	

}


