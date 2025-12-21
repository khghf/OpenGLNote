#pragma once
#include"../Window.h"
#include<glad/glad.h>
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
		virtual GLFWwindow* GetGlWindow()const { return static_cast<GLFWwindow*>(GetNativeWindow()); }
		virtual void* GetNativeWindow()const { return m_NativeWindow; };

	private:
		virtual void Init(const WindowProps& Props)override;
		void ShutDown();
		virtual bool ShouldClose()override;
	private:
		GLFWwindow* GL_Window;
		void* m_NativeWindow;
	};
}
#endif // DM_PLATFORM_WINDOW




