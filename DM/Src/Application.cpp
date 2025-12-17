#include"DMPCH.h"
#include "Application.h"
#include<GLFW/glfw3.h>
#include<Platform/Window/Win/WinWindow.h>


namespace DM {
	Application::Application()
	{
		Win = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
		OnExit();
	}


	void Application::Run()
	{
	
		const float& CurrentTime = glfwGetTime();
		float LastTime = 0.;
		const float& DeltaTime = CurrentTime - LastTime;
		LastTime = CurrentTime;
		glClearColor(0.f, 0.f, 1.f, 1.f);
		Start();
		while (!Win->ShouldClose())
		{
			Win->Update(DeltaTime);
			
		}
	}

	void Application::Start()
	{
	}

	void Application::Update(float DeltaTime)
	{
	}

	void Application::OnExit()
	{
	}
}
