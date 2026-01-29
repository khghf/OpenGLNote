#include "DMPCH.h"
#include "GActor.h"
#include"GWorld.h"
#include<entt/entt.hpp>
#include"GComponent.h"
namespace DM
{
	GActor::GActor(entt::entity entityHandle, GWorld* context):
		m_Handle(entityHandle),m_Context(context)
	{
		
	}

}


