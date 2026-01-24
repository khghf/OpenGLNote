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
		std::string m_Name = "Unnamed";
		std::string m_path;
		bool bHasSavedToLocal = false;//在本地序列化过
	private:
	private:
		entt::registry m_Registry;
		constexpr static std::string_view s_FileExtension = "scene";
	};
}

