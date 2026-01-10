#pragma once
#include<Core/Scene/Scene.h>
#include<Core/MMM/Reference.h>
#include<Core/Scene/Entity.h>
namespace DM
{
	class SceneHierarchyPanel
	{
		friend class EditorLayer;
		SceneHierarchyPanel(const Ref<Scene>context);
		void SetContext(const Ref<Scene>& context);
	private:
		void OnUIRender();
		void DrawEntityNode(const Entity& entity);
		void DrawComponents(const Entity& entity);
	private:
		Ref<Scene>m_Context;
		Entity m_SelectedEntity;
	};
}


