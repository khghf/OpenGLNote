#pragma once
#include <DMPCH.h>
#include<GEngine.h>
#include<FrameWork/GPlayer.h>
#include<FrameWork/GActor.h>
#ifdef  DM_PLATFORM_WINDOWS
int main(int argc, char** argv)
{
	const DM::GObject* const obj = new DM::GActor();
	const DM::GPlayer* const player = new DM::GPlayer();
	const DM::GActor* const entt = new DM::GActor();
	auto& data = mirror::GetGlobalData();
	/*std::cout << DM::GameStatic::IsChildOf<DM::GObject>(obj) << std::endl;
	std::cout << DM::GameStatic::IsChildOf<DM::GObject>(player) << std::endl;
	std::cout << DM::GameStatic::IsChildOf<DM::GObject>(entt) << std::endl;*/
	delete obj;
	delete player;
	delete entt;
	return 0;
}
#endif //  DM_PLATFORM_WINDOWS
