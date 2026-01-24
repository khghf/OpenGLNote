#pragma once
#include"Panel.h"
#include<Core/Scene/Entity.h>
namespace DM
{
	class SceneHierarchyPanel:public Panel
	{
		friend class EditorLayer;
		SceneHierarchyPanel(const Ref<Context>& context) { SetContext(context); };
	protected:
		virtual void Render()override;
		void DrawEntityNode(const Entity& entity);
		void DrawComponents(const Entity& entity);
	private:
		Entity m_SelectedEntity;
	};
}


