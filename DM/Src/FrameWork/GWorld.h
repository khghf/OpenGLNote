#pragma once
#include"GObject.h"
#include"GWorld.gen.h"
namespace DM
{
	class GActor;
	class CLASS() GWorld:public GObject
	{
		REFLECT_BODY()
		friend class GActor;
		friend class EditorLayer;
		friend class SceneHierarchyPanel;
		friend class Serializer;
		GWorld();
	public:
		~GWorld();
	public:
		GActor CreateEntity();
		void DestroyEntity(GActor entity);
		std::string m_Name = "Unnamed";
		std::string m_path;
		PROPERTY()
		bool bHasSavedToLocal = false;//在本地序列化过
	private:
		constexpr static std::string_view s_FileExtension = "world";
		entt::registry m_Registry;
	};
}

