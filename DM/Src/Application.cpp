#include"DMPCH.h"
#include "Application.h"
#include<GLFW/glfw3.h>
#include<Platform/Window/Win/WinWindow.h>
#include"Core/EventSystem/EventManager.h"
DECLARE_DELEGATE(TEST, void);
namespace DM {
	TEST test;
	Application::Application()
	{
		m_Win = std::unique_ptr<Window>(Window::Create());
		m_LayerStack = std::unique_ptr<LayerStack>(new LayerStack());
		test.BindLamFun([this]() {
			this->Start();
			});
		EventManager::GetInst()->Register<Event>([this](const Event* const e)
			{
				this->OnEvent(e);
			}
		);
	}

	Application::~Application()
	{
		OnExit();
	}


	void Application::Run()
	{
		test.Execute();
		const float& CurrentTime = glfwGetTime();
		float LastTime = 0.;
		const float& DeltaTime = CurrentTime - LastTime;
		LastTime = CurrentTime;
		glClearColor(0.f, 0.f, 1.f, 1.f);
		Start();
		while (!m_Win->ShouldClose())
		{
			m_Win->Update(DeltaTime);
		}
	}

	void Application::Start()
	{
		LOG_Core_INFO("STart");
	}

	void Application::Update(float DeltaTime)
	{
	}

	void Application::OnExit()
	{
	}
	void Application::OnEvent(const Event* const e)
	{
		for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();)
		{
			--it;
			if (!(*it))continue;
			(*it)->OnEvent(e);
			if (e->bHandled)break;
		}
		LOG_Core_INFO("{0},{1}", 3,this->m_LayerStack->Size());
	}
}
