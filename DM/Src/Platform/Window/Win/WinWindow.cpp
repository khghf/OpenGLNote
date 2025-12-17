#include "DMPCH.h"
#ifdef DM_PLATFORM_WINDOWS
#include "WinWindow.h"
#include"Core/Log.h"
#include<Core/EventSystem/Event/WindowEvent.h>
#include<Core/EventSystem/Event/MouseEvent.h>
#include<Core/EventSystem/Event/KeyEvent.h>
#include<Core/EventSystem/EventManager.h>
namespace DM
{
	WinWindow::WinWindow(const WindowProps& Props)
	{
		Init(Props);
	}

	WinWindow::~WinWindow()
	{
		ShutDown();
	}

	void WinWindow::Update(float DeltaTime)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(GL_Window);
		glfwPollEvents();
	}

	void WinWindow::Init(const WindowProps& Props)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GL_Window = glfwCreateWindow(Props.Width, Props.Height, Props.Title.c_str(), nullptr, nullptr);
		if (GL_Window == nullptr)
		{
			DM_CORE_ASSERT("Failed to Create GLFW Window");
			glfwTerminate();
		}
		glfwMakeContextCurrent(GL_Window);
		{
			glfwSetWindowSizeCallback
			(GL_Window, 
				[](GLFWwindow* window, int width, int height) 
				{ 
					static WindowResizeEvent e;
					e.Data.Size = width * height / 100;
					EventManager::GetInst()->OnEvent(&e);
				}
			);
			glfwSetMouseButtonCallback
			(GL_Window,
				[](GLFWwindow* window, int button, int action, int mods)
				{
					static MouseClick e;
					e.Data.KeyAction = static_cast<MouseClick::Action>(action);
					e.Data.key = button;
					glfwGetCursorPos(window, &e.Data.vec2, &e.Data.vec2);
					EventManager::GetInst()->OnEvent(&e);
				}
			);
			glfwSetScrollCallback
			(GL_Window,
				[](GLFWwindow* window, double xoffset, double yoffset)
				{
					static MouseScroll e;
					EventManager::GetInst()->OnEvent(&e);
				}
			);
			glfwSetKeyCallback
			(GL_Window,
				[](GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					static KeyClick e;
					e.Data.KeyAction = static_cast<KeyClick::Action>(action);
					e.Data.key = key;
					EventManager::GetInst()->OnEvent(&e);
				}
			);
		}
	}
	Window* Window::Create(const WindowProps& Props)
	{
		return new WinWindow(Props);
	}
	void WinWindow::ShutDown()
	{
		glfwDestroyWindow(GL_Window);
		glfwTerminate();
	}
	bool WinWindow::ShouldClose()
	{
		return glfwWindowShouldClose(GL_Window);
	}
}
#endif // DM_PLATFORM_WINDOW



