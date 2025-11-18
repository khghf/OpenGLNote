#include "Application.h"
#include<Window.h>
#include<GScence.h>
#include"AssetManager.h"
Application::Application()
{
	Win = std::make_unique<Window>(1440,1080,"MC");
	Scence = std::make_unique<GScence>();
}

Application::~Application()
{
	OnExit();
	std::cout << "~Application" << std::endl;
}

Application* Application::GetSingletion()
{
	static Application* APP = nullptr;
	if (APP == nullptr)
	{
		APP = new Application();
	}
	return APP;
}

void Application::Run()
{
	const float& CurrentTime = glfwGetTime();
	float LastTime = 0.;
	const float& DeltaTime = CurrentTime - LastTime;
	LastTime = CurrentTime;
	glClearColor(0.f, 0.f, 1.f, 1.f);
	Start();
	while (!glfwWindowShouldClose(Win->GetGlfwWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Update(DeltaTime);
		glfwSwapBuffers(Win.get()->GetGlfwWindow());
		glfwPollEvents();
	}
}

void Application::Start()
{
	if (!Win)
	{
		OnExit();
	}
	if (Scence)Scence->Start();
}

void Application::Update(float DeltaTime)
{
	if (Scence)Scence->Update(DeltaTime);
}

void Application::OnExit()
{
	if (Scence)Scence->OnDestroy();
}
