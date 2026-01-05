#pragma once
#include<Core/MMM/Reference.h>
namespace DM
{
	struct FrameBufferSpecification
	{
		uint32_t Width, Height;
		uint32_t Smaples = 1;
	};
	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer()=default;
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual uint32_t GetColorAttachmentId()const = 0;
		virtual uint32_t GetDepthAttachmentId()const = 0;
		virtual void Resize(uint32_t width,uint32_t height) = 0;
		virtual uint32_t GetId()const = 0;

		static Ref<FrameBuffer>Create(const FrameBufferSpecification& spec);
	};
	
}


