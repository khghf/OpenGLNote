#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include"DataType.h"
#include"AssetManager.h"
class Window
{
public:
	int Width, Height;
	std::string Title;
public:
	Window(const int& width, const int& height, const std::string& title) :Width(width), Height(height), Title(title) {
		Init();
		AssetManager::GetSingletion();
	}
	~Window();
private:
	GLFWwindow*GlfwWin;
private:
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator = (const Window&) = delete;
public:
	GLFWwindow* const GetGlfwWindow()const;
private:
	bool Init();
};
