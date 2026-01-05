#include<DMPCH.h>
#include"VertexArray.h"
#include"Renderer/Renderer.h"
#include<Platform/Render/OpenGl/OpenGlVertexArray.h>
namespace DM
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::EAPI::None:
			DM_CORE_ASSERT(false, "{}", "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::EAPI::OpenGl: return std::make_shared<OpenGlVertexArray>();
		}
		DM_CORE_ASSERT(false, "{}", "UnKnown RendererAPI!");
		return nullptr;
	}
}