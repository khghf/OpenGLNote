#pragma once
#include<GComponent.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
class CCamera :GComponent
{
private:
	glm::vec3 Location;
	glm::vec3 Up = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 Forward = glm::vec3(0.f, 0.f, 1.f);
	glm::vec3 Right = glm::vec3(1.f, 0.f, 0.f);
	float FOV=90.f;
	float NearPlane = 0.1f;//近平面
	float FarPlane = 100.f;//远平面
	float Pich = 0.f;//俯仰
	float Yaw = 0.f;//偏航
	float Roll = 0.f;//翻滚
public:
	CCamera();
	CCamera(const float X, const float Y, const float Z);
	CCamera(glm::vec3 Location);
	virtual void Start()override;
	virtual void Update(float DeltaTime)override;
	virtual void OnDestroy() override;
public:
	inline glm::mat4 GetViewMatrix() { return glm::lookAt(Location, Location + Forward, Up);}
};