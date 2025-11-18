#include"Application.h"
#include"GameStatic.h"
#include<iostream>
#include"Util.h"
int main()
{
	//HWND ConsoleWindow = GetConsoleWindow();
	//ShowWindow(ConsoleWindow, SW_HIDE);
	Application* APP = Application::GetSingletion();
	APP->Run();
	//Util::Print("11111","2222","3333");
	//std::cout << GameStatic::ConvertPathToName("../aaa/a/abc.text") << std::endl;
	delete APP;
	return 0;
}