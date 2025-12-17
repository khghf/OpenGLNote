#include "CameraComponent.h"

CCamera::CCamera()
{
	Location = glm::vec3(0.f, 0.f, 0.f);
}

CCamera::CCamera(const float X, const float Y, const float Z)
{
	Location = glm::vec3(X, Y, Z);
}

CCamera::CCamera(glm::vec3 Location):CCamera(Location.x,Location.y,Location.z)
{

}

void CCamera::Start()
{
}

void CCamera::Update(float DeltaTime)
{
}

void CCamera::OnDestroy()
{
}
