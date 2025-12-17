#pragma once
#include"../Window.h"
#include<GLFW/glfw3.h>
#ifdef DM_PLATFORM_WINDOWS
namespace DM
{
	class WinWindow :public Window
	{
	public:
		WinWindow(const WindowProps& Props);
		~WinWindow();
		virtual void Update(float DeltaTime)override;
	private:
		virtual void Init(const WindowProps& Props)override;
		void ShutDown();
		virtual bool ShouldClose()override;
	private:
		GLFWwindow* GL_Window;
	};
}
#endif // DM_PLATFORM_WINDOW




