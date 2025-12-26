#include "DMPCH.h"
#include "ImguiLayer.h"
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
	ImguiLayer::ImguiLayer():Layer("ImguiLayer")
	{

	}
	ImguiLayer::~ImguiLayer()
	{

	}
	void ImguiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui_ImplGlfw_InitForOpenGL(Application::GetInst()->GetWindow()->GetGlWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 450");
		LOG_Core_INFO("ImGui version:{}", ImGui::GetVersion());
	}
	void ImguiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	void ImguiLayer::OnUpdate(float DeltaTime)
	{
		ImGuiIO& IO = ImGui::GetIO();
		IO.DisplaySize = ImVec2(Application::GetInst()->GetWindow()->Width(), Application::GetInst()->GetWindow()->Height());
		float time = (float)glfwGetTime();
		IO.DeltaTime = m_Time > 0.f ? time - m_Time : (1.f / 60.f);
		m_Time = time;
		Begin();
		ImGuiRender();
		End();
	}
	void ImguiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//ImGui::Begin();
	}
	void ImguiLayer::ImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
	void ImguiLayer::End()
	{
		//ImGui::End();
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
	}
	//void ImguiLayer::OnEvent(Event* const e)
	//{
	//	Disptcher dis(e);
	//	dis.Disptch<KeyPress>([this](Event* const e)->bool {
	//		return OnKeyPressed(e);
	//		});
	//	dis.Disptch<KeyRelease>([this](Event* const e)->bool {
	//		return OnKeyReleased(e);
	//		});
	//	dis.Disptch<KeyRepeat>([this](Event* const e)->bool {
	//		return OnKeyRepeated(e);
	//		});
	//	dis.Disptch<KeyClick>([this](Event* const e)->bool {
	//		return OnKeyClicked(e);
	//		});
	//	dis.Disptch<KeyTyped>([this](Event* const e)->bool {
	//		return OnKeyTyped(e);
	//		});
	//	dis.Disptch<MouseClick>([this](Event* const e)->bool {
	//		return OnMouseClicked(e);
	//		});
	//	dis.Disptch<MousePress>([this](Event* const e)->bool {
	//		return OnMousePressed(e);
	//		});
	//	dis.Disptch<MouseRelease>([this](Event* const e)->bool {
	//		return OnMouseReleased(e);
	//		});
	//	dis.Disptch<MouseMove>([this](Event* const e)->bool {
	//		return OnMouseMove(e);
	//		});
	//	dis.Disptch<MouseScroll>([this](Event* const e)->bool {
	//		return OnMouseScroll(e);
	//		});
	//	dis.Disptch<WindowResize>([this](Event* const e)->bool {
	//		return OnWindowResize(e);
	//		});
	//}
	//bool ImguiLayer::OnKeyClicked(Event* const e)
	//{
	//	//LOG_Core_INFO("OnKeyClicked");
	//	return false;
	//}
	//bool ImguiLayer::OnKeyPressed(Event* const e)
	//{
	//	//LOG_Core_INFO("OnKeyPressed");
	//	ImGuiIO& io = ImGui::GetIO();
	//	ImGuiKey imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(e->GetData<KeyPress>()->key, e->GetData<KeyPress>()->scancode);
	//	UpdateKeyModifiers(io, Application::GetInst()->GetWindow()->GetGlWindow());
	//	io.AddKeyEvent(imgui_key, true);
	//	return false;
	//}
	//bool ImguiLayer::OnKeyRepeated(Event* const e)
	//{
	//	//LOG_Core_INFO("OnKeyRepeated");
	//	ImGuiIO& io = ImGui::GetIO();
	//	UpdateKeyModifiers(io, Application::GetInst()->GetWindow()->GetGlWindow());
	//	return false;
	//}
	//bool ImguiLayer::OnKeyReleased(Event* const e)
	//{
	//	//LOG_Core_INFO("OnKeyReleased");
	//	ImGuiIO& io = ImGui::GetIO();
	//	ImGuiKey imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(e->GetData<KeyRelease>()->key, e->GetData<KeyRelease>()->scancode);
	//	UpdateKeyModifiers(io, Application::GetInst()->GetWindow()->GetGlWindow());
	//	io.AddKeyEvent(imgui_key, false);
	//	return false;
	//}
	//bool ImguiLayer::OnKeyTyped(Event* const e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.AddInputCharacter(e->GetData<KeyTyped>()->KeyCode);
	//	return false;
	//}
	//bool ImguiLayer::OnMouseClicked(Event* const e)
	//{
	//	//LOG_Core_INFO("OnMouseClicked");
	//	return false;
	//}
	//bool ImguiLayer::OnMousePressed(Event* const e)
	//{
	//	//LOG_Core_INFO("OnMousePressed");
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.AddMouseButtonEvent(e->GetData<MousePress>()->button, true);
	//	return false;
	//}
	//bool ImguiLayer::OnMouseReleased(Event* const e)
	//{
	//	//LOG_Core_INFO("OnMouseReleased");
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.AddMouseButtonEvent(e->GetData<MouseRelease>()->button, false);
	//	return false;
	//}
	//bool ImguiLayer::OnMouseMove(Event* const e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.AddMousePosEvent(e->GetData<MouseMove>()->pos.x, e->GetData<MouseMove>()->pos.y);
	//	//LOG_Core_INFO("OnMouseMove:{},{}", e->GetData<MouseMove>()->pos.x, e->GetData<MouseMove>()->pos.y);
	//	return false;
	//}
	//bool ImguiLayer::OnMouseScroll(Event* const e)
	//{
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.AddMouseWheelEvent(e->GetData<MouseScroll>()->offset.x, e->GetData<MouseScroll>()->offset.y);
	//	return false;
	//}
	//bool ImguiLayer::OnWindowResize(Event* const e)
	//{
	//	int x = e->GetData<WindowResize>()->size.x;
	//	int y = e->GetData<WindowResize>()->size.y;
	//	Application::GetInst()->GetWindow()->SetWidth(x);
	//	Application::GetInst()->GetWindow()->SetHeight(y);
	//	glViewport(0, 0, x, y);
	//	ImGuiIO& io = ImGui::GetIO();
	//	io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
	//	return false;
	//}
	//void ImguiLayer::UpdateKeyModifiers(ImGuiIO& io, GLFWwindow* window)
	//{
	//	io.AddKeyEvent(ImGuiMod_Ctrl, (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS));
	//	io.AddKeyEvent(ImGuiMod_Shift, (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS));
	//	io.AddKeyEvent(ImGuiMod_Alt, (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS));
	//	io.AddKeyEvent(ImGuiMod_Super, (glfwGetKey(window, GLFW_KEY_LEFT_SUPER) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT_SUPER) == GLFW_PRESS));
	//}
}

