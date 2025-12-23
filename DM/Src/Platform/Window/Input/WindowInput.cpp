#include "DMPCH.h"
#include "WindowInput.h"
#include<GLFW/glfw3.h>
#include<Application.h>
namespace DM
{
	bool WindowInput::IsKeyPressedImpl(int KeyCode) const
	{
		auto state = glfwGetKey(static_cast<NativeWindow*>(Application::GetInst()->GetWindow()->GetNativeWindow()), KeyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowInput::IsMouseButtonPressedImpl(int Button) const
	{
		auto state = glfwGetMouseButton(static_cast<NativeWindow*>(Application::GetInst()->GetWindow()->GetNativeWindow()), Button);
		return state == GLFW_PRESS;
	}
	Vector2 WindowInput::GetMousePosImpl() const
	{
		double x = -1, y = -1;
		glfwGetCursorPos(static_cast<NativeWindow*>(Application::GetInst()->GetWindow()->GetNativeWindow()), &x, &y);
		return Vector2((float)x,(float)y);
	}
}

