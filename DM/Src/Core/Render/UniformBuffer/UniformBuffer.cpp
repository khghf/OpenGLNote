#include "DMPCH.h"
#include "UniformBuffer.h"
#include"../Renderer/Renderer.h"
#include"Platform/Render/OpenGl/UniformBuffer/OpenGlUniformBuffer.h"
namespace DM
{
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::EAPI::None:    DM_CORE_ASSERT(false, "{}RendererAPI::None is currently not supported!",""); return nullptr;
			case RendererAPI::EAPI::OpenGl:  return CreateRef<OpenGlUniformBuffer>(size, binding);
		}
		DM_CORE_ASSERT(false, "{}Unknown RendererAPI!","");
		return nullptr;
	}
}