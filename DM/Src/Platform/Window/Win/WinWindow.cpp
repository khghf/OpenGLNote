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
			//窗口大小回调
			glfwSetWindowSizeCallback
			(GL_Window, 
				[](GLFWwindow* window, int width, int height) 
				{ 
					static WindowResizeEvent e;
					e.Data.size.x = width;
					e.Data.size.y = height;
					EventManager::GetInst()->OnEvent(&e);
				}
			);
			//鼠标按键回调
			glfwSetMouseButtonCallback
			(GL_Window,
				[](GLFWwindow* window, int button, int action, int mods)
				{
					static MouseClick ec;
					static MousePress ep;
					static MouseRelease er;
					static int LastAction = -1;
					static double x = 0;
					static double y = 0;
					glfwGetCursorPos(window,&x,&y);
					auto set = [&](MouseClick*e) {
							e->Data.key = button;
							e->Data.pos.x = x;
							e->Data.pos.y = y;
						};
					if (LastAction == GLFW_PRESS && action == GLFW_RELEASE)
					{
						set(&er);
						set(&ec);
						EventManager::GetInst()->OnEvent(&er);
						EventManager::GetInst()->OnEvent(&ec);
					}
					else
					{
						switch (action)
						{
						case GLFW_PRESS:
						{
							set(&ep);
							EventManager::GetInst()->OnEvent(&ep);
							break;
						}
						case GLFW_RELEASE:
						{
							set(&er);
							EventManager::GetInst()->OnEvent(&er);
							break;
						}
						default:
							break;
						}
					}
					LastAction = action;
				}
			);
			//鼠标滚轮回调
			glfwSetScrollCallback
			(GL_Window,
				[](GLFWwindow* window, double xoffset, double yoffset)
				{
					static MouseScroll e;
					e.Data.offset.x = xoffset;
					e.Data.offset.y = yoffset;
					EventManager::GetInst()->OnEvent(&e);
				}
			);
			//键盘按键回调
			glfwSetKeyCallback
			(GL_Window,
				[](GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					static KeyClick ec;
					static KeyPress ep;
					static KeyRepeat ert;
					static KeyRelease ere;
					static int LastAction = -1;
					auto set = [&](KeyClick* e) {
						e->Data.key = key;
						};
					if (LastAction == GLFW_PRESS&&action==GLFW_RELEASE)
					{
						set(&ere);
						set(&ec);
						EventManager::GetInst()->OnEvent(&ere);
						EventManager::GetInst()->OnEvent(&ec);
					}
					else
					{
						switch (action)
						{
						case GLFW_PRESS:
						{
							set(&ep);
							EventManager::GetInst()->OnEvent(&ep);
							break;
						}
						case GLFW_REPEAT:
						{
							set(&ert);
							EventManager::GetInst()->OnEvent(&ert);
							break;
						}
						case GLFW_RELEASE:
						{
							set(&ere);
							EventManager::GetInst()->OnEvent(&ere);
							break;
						}
						default:
							break;
						}
					}
					LastAction = action;
				}
			);
			//光标移动回调
			glfwSetCursorPosCallback
			(GL_Window,
				[](GLFWwindow* window, double xpos, double ypos)
				{
					static MouseMove e;
					e.Data.pos.x = xpos;
					e.Data.pos.x = ypos;
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



