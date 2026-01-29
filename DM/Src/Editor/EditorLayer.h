#pragma once
#include<Core/Layer/ImGuiLayer.h>
#include<Core/Render/Camera/CameraController.h>
#include<GEngine.h>
#include<Core/Render/Renderer/Renderer2D.h>
#include<Resource/AssetManager.h>
#include<Core/Render/Texture/Texture.h>
#include<Tool/Util/TimeMeasurer.h>
#include<Core/Render/FrameBuffer/FrameBuffer.h>
#include"Core/Serializer.h"
#include<filesystem>
namespace DM
{
	class GWorld;
	class Panel;
	struct DockSpace
	{
		
	};
	struct ViewPort
	{
		Vector2 MinBound = { 0.f,0.f };//视口左下角
		Vector2 MaxBound = { 0.f,0.f };//视口右上角
		Vector2 Size = { 0.f,0.f };
		Vector2 MousePosLocal = { 0.f,0.f };//相对与视口左下角的坐标
		Vector2 MousePosScreen = { 0.f,0.f };//相对与屏幕左上角的坐标
		Vector2 MousePosLocalNarmal = { 0.f,0.f };
		bool bFocused=false;
		bool bHovered=false;
		void Reset()
		{
			MinBound = { 0.f,0.f };
			MaxBound = { 0.f,0.f };
			Size = { 0.f,0.f };
			MousePosLocal = { 0.f,0.f };
			MousePosScreen = { 0.f,0.f };
			MousePosLocalNarmal = { 0.f,0.f };
			bFocused = false;
			bHovered = false;
		}
	};
	
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

		void UpdateEditor();
		void UpdateRunTime();
	private:
		void OnSceneChanged();
		void RenderViewPort();
		void RenderSetting();

		void RenderMenuBar();
		void RenderMenuBar_File();
	private:
		void OpenScene(std::filesystem::path p);
	private:
		CameraController m_CameraController;
		Ref<FrameBuffer>m_ViewportFramebuffer;
		Ref<GWorld>m_ActiveScene;
		Ref<Panel>m_HierarchyPanel;
		Ref<Panel>m_ContentPanel;
		ViewPort m_ViewPort;
		enum class SceneState:uint8_t
		{

		};
	};



}
