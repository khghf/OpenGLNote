#include"D:\Projects\DM\DM\Src\FrameWork\GObject.h"
REGISTER_TYPE(DM::GObject)
REGISTER_PRIVATE_MEMBER(DM::GObject,test)
REGISTER_PRIVATE_MEMBER(DM::GObject,bEnableUpdate)
::mirror::TypeId DM::GObject::GetTypeId()
{
	return ::mirror::GetTypeId<DM::GObject>(); 
}
