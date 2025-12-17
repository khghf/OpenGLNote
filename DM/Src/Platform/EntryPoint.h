#pragma once
#include<Core/DelegateSystem/DelegateTest.h>
//#include<Core/DelegateSystem/DelegateMacro.h>
#include<Core/EventSystem/EventManager.h>
#ifdef  DM_PLATFORM_WINDOWS
class AAA
{
public:
	static  int a;
};
int AAA::a = 2;
class BBB:public AAA
{
public:
	static int a;

};
int BBB::a = 9;

extern DM::Application* DM::CreateApplication();
int main(int argc, char** argv)
{
	DM::Log::Init();
	/*EventManager::GetInst()->RegisterLam<KeyClick>([](const Event* const e)->void {
		std::cout <<e->GetData<KeyClick>()->key << std::endl;
		return;
		});*/
	//EventManager::GetInst()->RegisterLam<MouseClick>([](const Event* const e)->void {
	//	//std::cout << e->GetData<MouseClick>()->key << std::endl;
	//	std::cout << e->GetData<MouseClick>()->vec2 << std::endl;
	//	//std::cout << e->GetData<MouseClick>()->KeyAction << std::endl;
	//	return;
	//	});
	EventManager::GetInst()->RegisterLam<WindowResizeEvent>([](const Event* const e)->void {
		std::cout << e->GetData<WindowResizeEvent>()->Size << std::endl;
		return;
		});
	auto* app = DM::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif //  DM_PLATFORM_WINDOWS
