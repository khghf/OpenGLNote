#include "DMPCH.h"
#include "OrthoGraphicCamera.h"
#include<glm/gtc/matrix_transform.hpp>
#include<Core/EventSystem/Event/Event.h>
#include<Core/EventSystem/Event/WindowEvent.h>
namespace DM
{
	OrthoGraphicCamera::OrthoGraphicCamera(float aspectRatio)
	{
		SetProjection(aspectRatio);
	}
	
	void OrthoGraphicCamera::OnUpdate(float reletaTime)
	{
	}

	void OrthoGraphicCamera::SetProjection(const float& aspectRatio)
	{
		m_aspectRatio = aspectRatio;
		float zoom = m_FOV / 45.f;
		m_ProjectionMatrix = glm::ortho(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom, -1.f, 1.f);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthoGraphicCamera::OnFovUpdate()
	{
		m_FOV = m_FOV < 10 ? 10 : m_FOV;
		float zoom = m_FOV / 45.f;
		m_ProjectionMatrix = glm::ortho(-m_aspectRatio * zoom, m_aspectRatio * zoom, -zoom, zoom, -1.f, 1.f);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthoGraphicCamera::OnWindowResize(Event* const e)
	{
		m_aspectRatio = e->GetData<WindowResize>()->size.x / e->GetData<WindowResize>()->size.y;
		float zoom = m_FOV / 45.f;
		m_ProjectionMatrix = glm::ortho(-m_aspectRatio * zoom, m_aspectRatio * zoom, -zoom, zoom, -1.f, 1.f);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}

