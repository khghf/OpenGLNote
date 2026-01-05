#pragma once
#include<Application.h>
#include<regex>
#include<string>
#include<functional>
#ifdef  DM_PLATFORM_WINDOWS
extern DM::Application* DM::CreateApplication();
int main(int argc, char** argv)
{
	DM::Log::Init();
	
	auto* app = DM::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif //  DM_PLATFORM_WINDOWS
