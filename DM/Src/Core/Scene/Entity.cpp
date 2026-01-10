#include "DMPCH.h"
#include "Entity.h"
#include"Scene.h"
#include<entt.hpp>
#include"Components.h"
namespace DM
{
	Entity::Entity(entt::entity entityHandle, Scene* context):
		m_Handle(entityHandle),m_Context(context)
	{
		
	}

}


