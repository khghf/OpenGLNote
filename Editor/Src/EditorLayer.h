#pragma once
#include<Tool/Imgui/ImguiLayer.h>
#include<Core/Render/Camera/CameraController.h>
#include<Application.h>
#include<Core/Render/Renderer/Renderer2D.h>
#include<Resource/AssetManager.h>
#include<Core/Render/Texture/Texture.h>
#include<Tool/Util/TimeMeasurer.h>
#include<Core/Render/FrameBuffer/FrameBuffer.h>
#include<Core/Scene/SceneSerializer.h>
namespace DM
{
	class Scene;
	class SceneHierarchyPanel;
	class EditorLayer :public ImGuiLayer
	{
	public:
		EditorLayer(const std::string_view& name);
		virtual ~EditorLayer();
		virtual void OnAttach()override;
		
		virtual void OnDetach()override;
		
		virtual void OnUpdate(float DeltaTime)override;
		
		virtual void OnEvent(DM::Event* const e)override;

	protected:
		virtual void Render()override;
	private:
		void OnSceneChanged();
		void RenderMenuBar();
		void RenderMenuBar_File();
	private:
		CameraController m_CameraController;
		Ref<FrameBuffer>m_ViewportFramebuffer;
		Ref<Scene>m_ActiveScene;
		Ref<SceneHierarchyPanel>m_Panel;
		SceneSerializer m_SceneSerializer;
		bool m_bViewportFocused = false, m_bViewportHovered = false;
		Vector2 m_ViewportSize;
	};
}
