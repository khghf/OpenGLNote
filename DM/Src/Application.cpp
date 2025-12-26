#include"DMPCH.h"
#include "Application.h"
#include<GLFW/glfw3.h>
#include<Platform/Window/Win/WinWindow.h>
#include"Core/EventSystem/EventManager.h"
#include"Tool/Imgui/ImguiLayer.h"
#include<imgui.h>
#include<Platform/Render/ImGui/imgui_impl_glfw.h>
#include<Platform/Render/ImGui/imgui_impl_opengl3.h>
#include<glad/glad.h>
namespace DM {
	Application* Application::s_Inst = nullptr;
	Application::Application()
	{
		DM_CORE_ASSERT(!s_Inst,"{}", "Application already exists");
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
		m_LayerStack->PushOverLayer(new ImguiLayer());
	}
	Application::~Application()
	{
		OnExit();
		delete m_Win;
	}
	void Application::Run()
	{
		Start();
		float CurrentTime =0.f;
		float LastTime = 0.f;
		while (m_bRunning)
		{
			CurrentTime = glfwGetTime();
			const float& DeltaTime = CurrentTime - LastTime;
			LastTime = CurrentTime;
			Update(DeltaTime);
		}
	}
	void Application::Start()
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.f);

	}
	void Application::Update(float DeltaTime)
	{
		glfwPollEvents();
		m_LayerStack->Update(DeltaTime);
		m_Win->Update(DeltaTime);
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
