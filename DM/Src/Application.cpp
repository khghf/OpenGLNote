#include"DMPCH.h"
#include "Application.h"
#include<GLFW/glfw3.h>
#include<Platform/Window/Win/WinWindow.h>
#include"Core/EventSystem/EventManager.h"
#include"Tool/Imgui/ImguiLayer.h"
#include<imgui.h>
#include<Platform/Render/imgui_impl_opengl3.h>
#include<Platform/Render/imgui_impl_glfw.h>
namespace DM {
	Application* Application::s_Inst = nullptr;
	Application::Application()
	{
		DM_CORE_ASSERT(!s_Inst, "Application already exists");
		s_Inst = this;
		m_Win = Window::Create();
		m_LayerStack = std::unique_ptr<LayerStack>(new LayerStack());
		EventManager::GetInst()->Register<Event>([this](Event* const e)
			{
				this->OnEvent(e);
			}
		);
		EventManager::GetInst()->Register<WindowClose>([this](Event* const e)
			{
				this->m_bRunning = false;
				LOG_Core_INFO("CloseWindow");
			}
		);
		m_LayerStack->PushOverlay(new ImguiLayer());
	}
	Application::~Application()
	{
		OnExit();
		delete m_Win;
	}
	void Application::Run()
	{
		const float& CurrentTime = glfwGetTime();
		float LastTime = 0.;
		const float& DeltaTime = CurrentTime - LastTime;
		LastTime = CurrentTime;
		glClearColor(0.f, 0.f, 1.f, 1.f);
		Start();
		while (m_bRunning)
		{
			glfwPollEvents();
			m_Win->Update(DeltaTime);
			Update(DeltaTime);
			glfwSwapBuffers(m_Win->GetGlWindow());
		}
	}
	void Application::Start()
	{

	}
	void Application::Update(float DeltaTime)
	{
		m_LayerStack->Update();
	}
	void Application::OnExit()
	{

	}
	void Application::OnEvent(Event* const e)
	{
		for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();)
		{
			--it;
			if (!(*it))continue;
			(*it)->OnEvent(e);
			if (e->bHandled)break;
		}
	}
}
