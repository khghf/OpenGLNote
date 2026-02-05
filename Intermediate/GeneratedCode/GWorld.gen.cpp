#include"D:\Projects\DM\DM\Src\FrameWork\GWorld.h"
REGISTER_TYPE(DM::GWorld)
REGISTER_MEMBER(DM::GWorld,bHasSavedToLocal)
::mirror::TypeId DM::GWorld::GetTypeId()
{
	return ::mirror::GetTypeId<DM::GWorld>(); 
}
