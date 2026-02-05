#include"DMPCH.h"
#include "GObject.h"
namespace DM
{
	GObject::GObject()
	{
		EnableUpdate(true);
		//UpdateMannger::GetSingletion()->Add(SPtr<GObject>(this));
	}

	//void GObject::Start()
	//{

	//}

	void GObject::Update(float DeltaTime)
	{
	}

	void GObject::Destroy()
	{

	}

	void GObject::OnDestroy()
	{
	}
}


