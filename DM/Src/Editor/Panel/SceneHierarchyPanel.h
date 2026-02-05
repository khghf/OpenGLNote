#pragma once
#include"Panel.h"
#include"FrameWork/GActor.h"
namespace DM
{
	class SceneHierarchyPanel:public Panel
	{
		friend class EditorLayer;
		SceneHierarchyPanel(const Ref<GWorld>& context) { SetContext(context); };
	protected:
		virtual void Render()override;
		void DrawEntityNode(const GActor& entity);
		void DrawComponents(const GActor& entity);
	private:
		GActor m_SelectedEntity;
	};
}


