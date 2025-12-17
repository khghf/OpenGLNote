#include "GWorld.h"
#include<iostream>
#include"Chunk.h"
#include"Util.h"
GWorld::GWorld()
{

}

GWorld::~GWorld()
{
	std::cout << "~GWorld()" << std::endl;
}

void GWorld::Start()
{
	SPtr<GObject>TestChunk(new Chunk());
	ObjList.push_back(TestChunk);
	for (const SPtr<GObject>& Obj : ObjList)
	{
		if (Obj)Obj->Start();
		else
		{
			ObjList.remove(Obj);
			Util::Print("Remove");
		}
	}
}

void GWorld::Update(float DeltaTime)
{
	for (const SPtr<GObject>& Obj : ObjList)
	{
		if (Obj)
		{
			Obj->Update(DeltaTime);
		}
		else
		{
			ObjList.remove(Obj);
		}
	}
}

void GWorld::OnDestroy()
{
	for (const SPtr<GObject>& Obj : ObjList)
	{
		if (Obj)Obj->OnDestroy();
		else
		{
			ObjList.remove(Obj);
		}
	}
}
