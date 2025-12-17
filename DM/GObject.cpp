#include "GObject.h"
#include"Util.h"
GObject::GObject()
{
	EnableUpdate(true);
	//UpdateMannger::GetSingletion()->Add(SPtr<GObject>(this));
}

void GObject::Start()
{

}

void GObject::Update(float DeltaTime)
{
}

void GObject::OnDestroy()
{
}

