#pragma once
class IGObject
{
private:
	bool bEnableUpdate : 1;
public:
	virtual void Start() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void OnDestroy() {};

	inline void EnableUpdate(const bool& bEnable) { bEnableUpdate = bEnable; }
	inline bool IsEnableUpdate()const { return bEnableUpdate; }
	virtual ~IGObject() {};
};