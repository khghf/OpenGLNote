#include "DMPCH.h"
#include "ImGuiLayer.h"
#include<imgui.h>
#include<Platform/Render/ImGui/imgui_impl_glfw.h>
#include<Platform/Render/ImGui/imgui_impl_opengl3.h>
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<Application.h>
#include<Core/Log.h>
#include<Core/EventSystem/Disptcher.h>
#include<Core/EventSystem/Event/KeyEvent.h>
#include<Core/EventSystem/Event/MouseEvent.h>
#include<Core/EventSystem/Event/WindowEvent.h>
ImGuiKey ImGui_ImplGlfw_KeyToImGuiKey(int keycode, int scancode);
namespace DM
{
	struct ImGuiContext
	{
		uint32_t RefTimes = 0;//当前用到imgui的layer的数量
		uint32_t BeginTimes = 0;//当前帧调用开始新帧函数的次数
		uint32_t RenderTimes = 0;//当前帧调用渲染帧的函数的次数
		float m_Time = 0.f;
		void Init()
		{
			++RefTimes;
			if (RefTimes >1)return;
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGui::StyleColorsDark();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			ImGui_ImplGlfw_InitForOpenGL(Application::GetInst()->GetWindow()->GetGlWindow(), true);
			ImGui_ImplOpenGL3_Init("#version 450");
			LOG_CORE_INFO("ImGui version:{}", ImGui::GetVersion());
		}
		void ShoutDown()
		{
			--RefTimes;
			if (RefTimes>0)return;
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}
		void BeginFrame()
		{
			++BeginTimes;
			if (BeginTimes>1)return;
			ImGuiIO& IO = ImGui::GetIO();
			IO.DisplaySize = ImVec2((float)Application::GetInst()->GetWindow()->Width(), (float)Application::GetInst()->GetWindow()->Height());
			float time = (float)glfwGetTime();
			IO.DeltaTime = m_Time > 0.f ? time - m_Time : (1.f / 60.f);
			m_Time = time;
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}
		void Render()
		{
			++RenderTimes;
			if (RenderTimes<RefTimes)return;
			ImGuiIO& io = ImGui::GetIO();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backupWin = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backupWin);
			}
			BeginTimes = 0;
			RenderTimes = 0;
		}
	};
	static ImGuiContext* s_UIContext = nullptr;
	ImGuiLayer::ImGuiLayer(std::string_view name):Layer(name)
	{
		
	}
	ImGuiLayer::~ImGuiLayer()
	{
		
	}
	void ImGuiLayer::OnAttach()
	{
		if (s_UIContext == nullptr)s_UIContext = new ImGuiContext();
		s_UIContext->Init();
	}
	void ImGuiLayer::OnDetach()
	{
		s_UIContext->ShoutDown();
		if (s_UIContext->RefTimes <= 0)
		{
			delete s_UIContext;
			s_UIContext = nullptr;
		}
	}

	void ImGuiLayer::OnEvent(Event* const e)
	{
		if (m_bBlockEvent)
		{
			ImGuiIO& io = ImGui::GetIO();
			e->bHandled |= e->IsInCategory(EEventCategory::MouseEvent) & io.WantCaptureMouse;
			e->bHandled |= e->IsInCategory(EEventCategory::KeyEvent) & io.WantCaptureKeyboard;
		}
		//LOG_CORE_INFO("e->bHandled:{}", e->bHandled);
		//LOG_CORE_INFO("m_bBlockEvent:{}", m_bBlockEvent);
	}

	void ImGuiLayer::OnUpdate(float DeltaTime)
	{
	}
	void ImGuiLayer::Begin()
	{
		s_UIContext->BeginFrame();
	}
	void ImGuiLayer::Render()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
	
	void ImGuiLayer::End()
	{
		s_UIContext->Render();
	}
}

