#pragma once
#include"DMPCH.h"
#include"Core/Core.h"
struct GLFWwindow;
namespace DM
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width, Height;
		WindowProps(const unsigned int Width=1280,const unsigned int Height=720,const std::string&Title="DM Engine")
		:Width(Width), Height(Height), Title(Title){}
	};
	class DM_API Window
	{
	public:
		virtual ~Window() {}
		virtual void Update(float DeltaTime) = 0;
		static Window* Create(const WindowProps& Props = WindowProps());
		virtual bool ShouldClose() = 0;
		virtual GLFWwindow* GetGlWindow()const = 0;
		virtual void* GetNativeWindow()const = 0;
		virtual void SetVSync(bool bEnanle)=0;
		bool IsEnableVSync()const { return bIsEnableVSync; }
		inline int Width()const { return m_WindowProps.Width; }
		inline int Height()const { return m_WindowProps.Height; }
		inline void SetWidth(const int& val) { m_WindowProps.Width = val; }
		inline void SetHeight(const int& val) { m_WindowProps.Height = val; }
	protected:
		virtual void Init(const WindowProps& Props)=0;
		WindowProps m_WindowProps;
		bool bIsEnableVSync = false;
	};
}