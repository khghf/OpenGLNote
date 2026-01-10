#include "DMPCH.h"
#include "Scene.h"
#include"Components.h"
#include"Entity.h"

namespace DM
{
    Scene::Scene()
    {
    }
    Scene::~Scene()
    {
    }
	Entity Scene::CreateEntity()
	{
        Entity en{ m_Registry.create(),this };
		en.AddComponent<TagComponent>("Unnamed Entity");
		en.AddComponent<TransformComponent>();
		en.AddComponent<SpriteComponent>();
        return en;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

}