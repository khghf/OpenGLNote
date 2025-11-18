#include "GScence.h"
#include<GWorld.h>
#include<iostream>
#include<AssetManager.h>
GScence::GScence()
{
	World = std::make_unique<GWorld>();
}

GScence::~GScence()
{
	std::cout << "~GScence" << std::endl;
}

void GScence::Start()
{
	if(World)World->Start();
}

void GScence::Update(float DeltaTime)
{
	if (World)World->Update(DeltaTime);
}

void GScence::OnDestroy()
{
	if (World)World->OnDestroy();
}
