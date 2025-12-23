#pragma once
#include<Core/Input/Input.h>
struct GLFWwindow;
namespace DM
{
	class WindowInput :public Input
	{
		using NativeWindow = GLFWwindow;
	protected:
		virtual bool IsKeyPressedImpl(int KeyCode)const override;
		virtual bool IsMouseButtonPressedImpl(int Button)const override;
		virtual Vector2 GetMousePosImpl()const override;
	};
}


