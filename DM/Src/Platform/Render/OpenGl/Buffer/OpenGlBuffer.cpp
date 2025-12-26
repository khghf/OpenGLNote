#include<DMPCH.h>
#include "OpenGlBuffer.h"
#include<glad/glad.h>
namespace DM
{
	/////////////////////////////////////////////////////////////VertexBuffer///////////////////////////////////////////////////////////////
	OpenGlVertexBuffer::OpenGlVertexBuffer(float* vertices, uint32_t elementCount)
	{
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * elementCount, vertices, GL_STATIC_DRAW);
	}
	void OpenGlVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	}
	void OpenGlVertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER,0);
	}
	/////////////////////////////////////////////////////////////IndexBuffer///////////////////////////////////////////////////////////////
	OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t* indices, uint32_t elementCount):m_Count(elementCount)
	{
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * elementCount, indices, GL_STATIC_DRAW);
	}
	void OpenGlIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
	}
	void OpenGlIndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	uint32_t OpenGlIndexBuffer::GetCount() const
	{
		return m_Count;
	}
}