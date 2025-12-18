#pragma once
#include"DMPCH.h"
#include"Core/Core.h"
#include<Core/DMType.h>
#include<Platform/Window/Window.h>
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
	private:
		virtual void Start();
		virtual void Update(float DeltaTime);
		virtual void OnExit();
		void OnEvent(const Event* const e);
	private:
		std::unique_ptr<Window>m_Win;
		UPtr<LayerStack>m_LayerStack;
	};
	Application*CreateApplication();
}
