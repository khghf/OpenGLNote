#pragma once
#include<GObject.h>
class GWorld;
class AssetManager;
class GScence :public GObject
{
public:
	GScence();
	~GScence();
private:
	UPtr<GWorld>World;
public:
	virtual void Start()override;
	virtual void Update(float DeltaTime)override;
	virtual void OnDestroy()override;
};