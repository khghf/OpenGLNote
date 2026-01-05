#pragma once
#include<Core/Render/FrameBuffer/FrameBuffer.h>

namespace DM
{

	class OpenGlFrameBuffer:public FrameBuffer
	{
	public:
		OpenGlFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGlFrameBuffer();
		virtual void Bind()override;
		virtual void UnBind()override;
		virtual uint32_t GetColorAttachmentId()const { return m_ColorAttachment; }
		virtual uint32_t GetDepthAttachmentId()const { return m_DepthAttachment; }
		virtual void Resize(uint32_t width, uint32_t height)override;
		virtual uint32_t GetId()const override { return m_Id; };

	private:
		void FreeBuffer();
		void Reset();
	private:
		FrameBufferSpecification m_Spec;
		uint32_t m_Id;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
	};
}


