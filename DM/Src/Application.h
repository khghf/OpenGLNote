#pragma once
#include"DMPCH.h"
#include"Core/Core.h"
#include<Platform/Window/Window.h>
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
	private:
		std::unique_ptr<Window>Win;
	};
	Application*CreateApplication();
}
