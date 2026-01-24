#pragma once
#include<IGObject.h>
#include<DataType.h>
class GObject:public IGObject
{
public:
	GObject();
	virtual~GObject() {}
public:
	virtual void Start()override;
	virtual void Update(float DeltaTime)override;
	virtual void OnDestroy() override;
private:
};