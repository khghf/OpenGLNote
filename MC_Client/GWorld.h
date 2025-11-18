#pragma once
#include<GObject.h>
#include<list>
class GWorld :public GObject
{
public:
	GWorld();
	~GWorld();
private:
	std::list<SPtr<GObject>>ObjList;
public:
	virtual void Start()override;
	virtual void Update(float DeltaTime)override;
	virtual void OnDestroy()override;
};