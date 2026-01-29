#pragma once
#include<entt/entt.hpp>
#include"GWorld.h"
#include<Core/Core.h>
#include"GObject.h"
#include<GActor.gen.h>
namespace DM
{
	class CLASS() GActor:public GObject
	{
		REFLECT_BODY()
		friend class GWorld;
		friend class SceneHierarchyPanel;
	public:
		GActor() = default;
		GActor(entt::entity entityHandle, GWorld* context);
		template<typename T>
		bool HasComponent()const { return m_Context->m_Registry.any_of<T>(m_Handle); }
		template<typename T,typename...Args>
		T& AddComponent(Args&&...arg) 
		{
			if (HasComponent<T>()) { LOG_CORE_WARN("Entity already has component!"); return T{}; }
			return m_Context->m_Registry.emplace<T>(m_Handle, std::forward<Args>(arg)...);
		}
		template<typename T>
		void RemoveComponent() 
		{ 
			if (!HasComponent<T>()) { LOG_CORE_WARN("Entity does not have component,need not to remove")return; }
			return m_Context->m_Registry.get<T>(m_Handle); 
		}
		template<typename T>
		T& GetComponent()const 
		{
			if (!HasComponent<T>()) { LOG_CORE_WARN("Entity does not have component!"); return T{}; }
			return m_Context->m_Registry.get<T>(m_Handle); 
		}
		operator bool()const { return m_Handle != entt::null; }
		operator entt::entity()const { return m_Handle; }
		bool operator==(const GActor& other) { return m_Handle == other.m_Handle; }
		bool operator!=(const GActor& other) { return !(*this == other); }
	private:
		entt::entity m_Handle{ entt::null };
		GWorld* m_Context=nullptr;
		PROPERTY()
			std::string M__name = "Entity";
	};

	class ScritableEntity
	{
	public:
		virtual ~ScritableEntity() = default;
	protected:
		virtual void OnCreate() {};
		virtual void OnUpdate(float deltaTime) {};
		virtual void OnDestroy() {};
	private:
		GActor m_Entity;
	};
}


