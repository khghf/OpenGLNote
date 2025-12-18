#pragma once
#include<Core/DelegateSystem/DelegateTest.h>
#include<Core/EventSystem/EventManager.h>
#ifdef  DM_PLATFORM_WINDOWS
extern DM::Application* DM::CreateApplication();
int main(int argc, char** argv)
{
	DM::Log::Init();
	/*DM::EventManager::GetInst()->Register<DM::WindowResizeEvent>([](const DM::Event* const e)->void {
		std::cout << e->GetData<DM::WindowResizeEvent>()->size.x << std::endl;
		return;
		});*/
	auto* app = DM::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif //  DM_PLATFORM_WINDOWS
