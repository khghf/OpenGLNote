#include "DMPCH.h"
#include "OrthoGraphicCamera.h"
#include<glm/gtc/matrix_transform.hpp>
namespace DM
{
	OrthoGraphicCamera::OrthoGraphicCamera(float top, float bottom, float left, float right):
	m_ProjectionMatrix(glm::ortho(left,right,bottom,top,-1.f,1.f)),m_ViewMatrix(Matrix4(1.f)), m_ProjectionViewMatrix(Matrix4(1.f)),m_Position(0.f)
	{

	}
	void OrthoGraphicCamera::ReCalculateViewMatrix()
	{
		Matrix4 transform=glm::translate(Matrix4(1.f), m_Position);
		transform = glm::rotate(transform, glm::radians(m_Rotation), Vector3(0.f,0.f,1.f));
		m_ViewMatrix = glm::inverse(transform);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}

