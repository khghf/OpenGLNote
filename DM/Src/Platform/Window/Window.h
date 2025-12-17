#pragma once
#include"DMPCH.h"
#include"Core/Core.h"
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
	protected:
		virtual void Init(const WindowProps& Props)=0;
	};
}