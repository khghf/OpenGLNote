#pragma once
#include<entt.hpp>
namespace DM
{
	class Entity;
	class Scene
	{
		friend class Entity;
		friend class EditorLayer;
		friend class SceneHierarchyPanel;
		friend class SceneSerializer;
		Scene();
	public:
		~Scene();
	public:
		Entity CreateEntity();
		void DestroyEntity(Entity entity);
	private:
	private:
		entt::registry m_Registry;
	};
}

