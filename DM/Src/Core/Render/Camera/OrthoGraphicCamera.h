#pragma once
#include<Core/Math/Vector.h>
#include<Core/Math/Matrix.h>
namespace DM
{
	class OrthoGraphicCamera
	{
	public:
		OrthoGraphicCamera(float top, float bottom, float left, float right);
		void SetPosition(const Vector3& position) { m_Position = position; ReCalculateViewMatrix(); }
		void SetRotation(const float& rotation) { m_Rotation = rotation; ReCalculateViewMatrix(); }
		const Vector3& GetPosition()const { return m_Position; }
		const Matrix4& GetProjectionMatrix()const { return m_ProjectionMatrix; }
		const Matrix4& GetViewMatrix()const { return m_ViewMatrix; }
		const Matrix4& GetProjectionViewMatrix()const { return m_ProjectionMatrix; }
	private:
		void ReCalculateViewMatrix();
	private:
		Matrix4 m_ProjectionMatrix;
		Matrix4 m_ViewMatrix;
		Matrix4 m_ProjectionViewMatrix;
		Vector3 m_Position;
		float m_Rotation = 0.f;
	};
}