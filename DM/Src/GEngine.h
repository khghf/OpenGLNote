#pragma once
#include"DMPCH.h"
#include"Core/Core.h"
#include<Core/Window.h>
#include"Core/Layer/LayerStack.h"
#include<Core/EventSystem/Event/Event.h>
#include<Core/MMM/Reference.h>
#include <Core/Layer/ImGuiLayer.h>
#include <Editor/EditorLayer.h>
#include<FrameWork/GObject.h>
namespace DM {
	class  GEngine
	{
	public:
		GEngine();
		virtual ~GEngine();
		void Run();
		inline Window const* GetWindow()const { return m_Win.get(); }
		void PushLayer(Layer* layer) { m_LayerStack->PushLayer(layer); }
		void PushOverLayer(Layer* layer) { m_LayerStack->PushOverLayer(layer); }
		void Close() { bRunning = false; }
		bool BlockEvent(bool bBlock) { return m_ImGuiLayer->BlockEvent(bBlock); }
	private:
		void Init();
		virtual void Start();
		virtual void Update(float DeltaTime);
		virtual void OnExit();
		void OnEvent(Event* const e);
		void OnWindowResize(Event* const e);
	protected:
		Scope<LayerStack>m_LayerStack;
	private:
		Ref<Window>m_Win;
		bool bRunning :1;
		bool bMinimized:1;
		static bool bAlreadyInit;
		Scope<ImGuiLayer>m_ImGuiLayer = nullptr;//ImGuilayers里最上层,可以在这一层阻断事件;
		Scope<EditorLayer>m_EditorLayer = nullptr;
	};
	extern GEngine* Engine;
}
