#include"DMPCH.h"
#include "Application.h"
#include<GLFW/glfw3.h>
#include"Core/EventSystem/EventManager.h"
#include<glad/glad.h>
#include<Resource/AssetManager.h>
#include<Core/EventSystem/Event/WindowEvent.h>
#include<Core/Render/Renderer/Renderer.h>
#include<Tool/Util/TimeMeasurer.h>
#include<Core/Input/Input.h>
namespace DM {
	Application* Application::s_Inst = nullptr;
	Application::Application()
	{
		DM_CORE_ASSERT(!s_Inst,"{}", "Application already exists");
		s_Inst = this;
		Init();
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
			CurrentTime = (float)glfwGetTime();
			const float& DeltaTime = CurrentTime - LastTime;
			LastTime = CurrentTime;
			Update(DeltaTime);
		}
	}
	void Application::Init()
	{
		m_Win = Window::Create();
		m_LayerStack = std::unique_ptr<LayerStack>(new LayerStack());
		
		EventManager::GetInst()->Register<Event>([this](Event* const e){this->OnEvent(e);});
		EventManager::GetInst()->Register<WindowClose>([this](Event* const e){this->m_bRunning = false;LOG_CORE_INFO("CloseWindow");});
		EventManager::GetInst()->Register<WindowResize>([this](Event* const e) {this->OnWindowResize(e); });
		Renderer::Init();
		m_ImguiLayer = CreateScope<ImGuiLayer>("ImguiBottomLayer");//imguilayers里的最顶层,可以在这一层阻断事件;

#ifdef PROFILE_SCOPE
		//m_LayerStack->PushOverLayer(TimeMeasurerLayer::GetInst());
#endif // PROFILE_SCOPE

		AssetManager::GetInst()->LoadAsset();
	}
	void Application::Start()
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	}
	void Application::Update(float DeltaTime)
	{
		if (Input::IsKeyPressed(Key::Escape))Close();
		glfwPollEvents();
		m_LayerStack->Update(DeltaTime);
		if (!m_bMinimized)
		{
			m_Win->Update(DeltaTime);
		}
	}
	void Application::OnExit()
	{

	}
	void Application::OnEvent(Event* const e)
	{
		m_ImguiLayer->OnEvent(e);
		for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();)
		{
			--it;
			if ((*it)==nullptr)continue;
			if (e->bHandled)break;
			(*it)->OnEvent(e);
		}
	}
	void Application::OnWindowResize(Event* const e)
	{
		const float w = e->GetData<WindowResize>()->size.x;
		const float h = e->GetData<WindowResize>()->size.y;
		if (w == 0 || h == 0)
		{
			m_bMinimized = true;
			return;
		}
		m_bMinimized = false;
		LOG_CORE_INFO("OnWindowResize");
		Renderer::OnWindowResize((uint32_t)w, (uint32_t)h);
	}
}
