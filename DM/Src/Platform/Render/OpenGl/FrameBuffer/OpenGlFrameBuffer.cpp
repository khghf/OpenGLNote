#include "DMPCH.h"
#include "OpenGlFrameBuffer.h"
#include<Core/Render/Renderer/Renderer.h>
#include<glad/glad.h>
namespace DM
{
	static uint32_t s_MaxFrameBufferSize = 8192;
	OpenGlFrameBuffer::OpenGlFrameBuffer(const FrameBufferSpecification& spec):
		m_Spec(spec),m_Id(0)
	{
		Reset();
	}

	OpenGlFrameBuffer::~OpenGlFrameBuffer()
	{
		FreeBuffer();
	}
	void OpenGlFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
	}
	void OpenGlFrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGlFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width <= 0 || height <= 0 || width > s_MaxFrameBufferSize || height > s_MaxFrameBufferSize)
		{
			LOG_CORE_ERROR("Attemp to resize framebuffer to[width:{},height:{}]", width, height);
			return;
		}
		m_Spec.Width = width;
		m_Spec.Height = height;
		Reset();
	}

	void OpenGlFrameBuffer::FreeBuffer()
	{
		if (m_Id)
		{
			glDeleteFramebuffers(1, &m_Id);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
		}
	}

	void OpenGlFrameBuffer::Reset()
	{
		FreeBuffer();
		glCreateFramebuffers(1, &m_Id);
		glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
		//颜色附件
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTextureStorage2D(m_ColorAttachment, 1, GL_RGBA8, m_Spec.Width, m_Spec.Height);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Spec.Width, m_Spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
		//深度附件
		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTextureStorage2D(m_DepthAttachment, 1, GL_DEPTH24_STENCIL8, m_Spec.Width, m_Spec.Height);
		glTextureParameteri(m_DepthAttachment, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_DepthAttachment, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_DepthAttachment, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_DepthAttachment, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);
		
		DM_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER)== GL_FRAMEBUFFER_COMPLETE, "{}", "Framebuffer is incompleted!");
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}