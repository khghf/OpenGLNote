#pragma once
#include<GObject.h>
class GComponent :public GObject
{
public:
	GComponent();
	~GComponent();
public:
	virtual void Start()override;
	virtual void Update(float DeltaTime)override;
	virtual void OnDestroy() override;
};
