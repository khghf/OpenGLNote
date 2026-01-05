#pragma once
#include"DMPCH.h"
#include"Core/Core.h"
#include<Core/Window.h>
#include"Core/Layer/LayerStack.h"
#include<Core/EventSystem/Event/Event.h>
#include<Core/MMM/Reference.h>
#include <Tool/Imgui/ImguiLayer.h>
namespace DM {
	class  Application
	{
	protected:
		Application();
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;
	public:
		virtual ~Application();
		void Run();
		inline static Application* GetInst(){ return s_Inst; }
		inline Window* GetWindow()const { return m_Win; }
		void PushLayer(Layer* layer) { m_LayerStack->PushLayer(layer); }
		void PushOverLayer(Layer* layer) { m_LayerStack->PushOverLayer(layer); }
		void Close() { m_bRunning = false; }
		bool BlockEvent(bool bBlock) { return m_ImguiLayer->BlockEvent(bBlock); }
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
		Window*m_Win;
		static Application* s_Inst;
		bool m_bRunning = true;
		bool m_bMinimized = false;
		Scope<ImGuiLayer>m_ImguiLayer = nullptr;//imguilayers里最底层,可以在这一层阻断事件;
	};
	Application*CreateApplication();
}
