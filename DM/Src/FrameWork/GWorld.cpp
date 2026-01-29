#include "DMPCH.h"
#include "GWorld.h"
#include"GComponent.h"
#include"GActor.h"

namespace DM
{
    GWorld::GWorld()
    {
    }
    GWorld::~GWorld()
    {
    }
	GActor GWorld::CreateEntity()
	{
        GActor en{ m_Registry.create(),this };
		en.AddComponent<TagComponent>("Unnamed Entity");
		en.AddComponent<TransformComponent>();
		en.AddComponent<SpriteComponent>();
        return en;
	}

	void GWorld::DestroyEntity(GActor entity)
	{
		m_Registry.destroy(entity);
	}

}