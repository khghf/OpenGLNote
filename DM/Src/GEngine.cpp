#include"DMPCH.h"
#include"GEngine.h"
#include<GLFW/glfw3.h>
#include"Core/EventSystem/EventManager.h"
#include<glad/glad.h>
#include<Resource/AssetManager.h>
#include<Core/EventSystem/Event/WindowEvent.h>
#include<Core/Render/Renderer/Renderer.h>
#include<Tool/Util/TimeMeasurer.h>
#include<Core/Input/Input.h>
#include"Config.h"
namespace DM {
	bool GEngine::bAlreadyInit = false;
	GEngine*Engine = nullptr;
	GEngine::GEngine()
	{
		DM_CORE_ASSERT(!bAlreadyInit, "{}", "");
		Init();
		bAlreadyInit = true;
	}
	GEngine::~GEngine()
	{
	}
	void GEngine::Run()
	{
		Start();
		float CurrentTime =0.f;
		float LastTime = 0.f;
		while (bRunning)
		{
			CurrentTime = (float)glfwGetTime();
			const float& DeltaTime = CurrentTime - LastTime;
			LastTime = CurrentTime;
			Update(DeltaTime);
		}
		OnExit();
	}
	void GEngine::Init()
	{
		Config::Init();
		m_Win =CreateRef<Window>(Window::Create()) ;
		m_LayerStack = std::unique_ptr<LayerStack>(new LayerStack());
		EventManager::GetInst()->Register<Event>([this](Event* const e){this->OnEvent(e);});
		EventManager::GetInst()->Register<WindowClose>([this](Event* const e){this->bRunning = false;LOG_CORE_INFO("CloseWindow");});
		EventManager::GetInst()->Register<WindowResize>([this](Event* const e) {this->OnWindowResize(e); });
		Renderer::Init();
		m_ImGuiLayer = CreateScope<ImGuiLayer>("TopLayer");//最顶层不属于LayerStack,可以在这一层阻断事件;
		m_EditorLayer= CreateScope<EditorLayer>("EditorLayer");
#ifdef PROFILE_SCOPE
		//m_LayerStack->PushOverLayer(TimeMeasurerLayer::GetInst());
#endif // PROFILE_SCOPE

		AssetManager::GetInst()->LoadAsset();
	}
	void GEngine::Start()
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	}
	void GEngine::Update(float DeltaTime)
	{
		if (Input::IsKeyPressed(Key::Escape))Close();
		glfwPollEvents();
		m_EditorLayer->OnUpdate(DeltaTime);
		m_LayerStack->Update(DeltaTime);
		if (!bMinimized)
		{
			m_Win->Update(DeltaTime);
		}
	}
	void GEngine::OnExit()
	{

	}
	void GEngine::OnEvent(Event* const e)
	{
		m_ImGuiLayer->OnEvent(e);
		m_EditorLayer->OnEvent(e);
		for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();)
		{
			--it;
			if ((*it)==nullptr)continue;
			if (e->bHandled)break;
			(*it)->OnEvent(e);
		}
	}
	void GEngine::OnWindowResize(Event* const e)
	{
		const float w = e->GetData<WindowResize>()->size.x;
		const float h = e->GetData<WindowResize>()->size.y;
		if (w == 0 || h == 0)
		{
			bMinimized = true;
			return;
		}
		bMinimized = false;
		LOG_CORE_INFO("OnWindowResize");
		Renderer::OnWindowResize((uint32_t)w, (uint32_t)h);
	}
}
