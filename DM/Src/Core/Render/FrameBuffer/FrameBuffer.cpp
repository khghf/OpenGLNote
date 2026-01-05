#include "DMPCH.h"
#include "FrameBuffer.h"
#include<Core/Render/Renderer/Renderer.h>
#include<Platform/Render/OpenGl/FrameBuffer/OpenGlFrameBuffer.h>
namespace DM
{

	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::EAPI::None:DM_CORE_ASSERT(false, "{}", "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::EAPI::OpenGl: return CreateRef<OpenGlFrameBuffer>(spec);
		}
		DM_CORE_ASSERT(false, "{}", "UnKnown RendererAPI!");
		return Ref<FrameBuffer>();
	}

}