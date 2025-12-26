#pragma once
#include"DMPCH.h"
#include"Core/Core.h"
#include<Core/DMType.h>
#include<Core/Window.h>
#include"Core/Layer/LayerStack.h"
#include<Core/EventSystem/Event/Event.h>
namespace DM {
	class DM_API Application
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
	private:
		virtual void Start();
		virtual void Update(float DeltaTime);
		virtual void OnExit();
		void OnEvent(Event* const e);
	protected:
		Scope<LayerStack>m_LayerStack;
	private:
		Window*m_Win;
		static Application* s_Inst;
		bool m_bRunning = true;
	};
	Application*CreateApplication();
}
