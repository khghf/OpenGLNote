#include "DMPCH.h"
#include<GLFW/glfw3.h>
#include<GEngine.h>
#include<Core/Input/Input.h>
namespace DM
{
	bool Input::IsKeyPressed(Key code) 
	{
		auto state = glfwGetKey(static_cast<GLFWwindow*>(Engine->GetWindow()->GetNativeWindow()), (int)code);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	
	bool Input::IsMouseButtonPressed(Key code)
	{
		auto state = glfwGetMouseButton(static_cast<GLFWwindow*>(Engine->GetWindow()->GetNativeWindow()), (int)code);
		return state == GLFW_PRESS;
	}
	Vector2 Input::GetMousePos() 
	{
		double x = -1, y = -1;
		glfwGetCursorPos(static_cast<GLFWwindow*>(Engine->GetWindow()->GetNativeWindow()), &x, &y);
		return Vector2((float)x,(float)y);
	}
}

