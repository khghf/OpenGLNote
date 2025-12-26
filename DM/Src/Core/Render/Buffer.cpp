#include "DMPCH.h"
#include "Buffer.h"
#include"Renderer/Renderer.h"
#include<Core/Log.h>
#include<Platform/Render/OpenGl/Buffer/OpenGlBuffer.h>
namespace DM
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t elementCount)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::EAPI::None:
			DM_CORE_ASSERT(false,"{}", "RendererAPI::None is currently not supported!");
			return nullptr;
			break; 
		case RendererAPI::EAPI::OpenGl:
			return new OpenGlVertexBuffer(vertices, elementCount);
			break;
		default:
			DM_CORE_ASSERT(false,"{}", "UnKnown RendererAPI!");
			break;
		}
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t elementCount)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::EAPI::None:
			DM_CORE_ASSERT(false, "{}", "RendererAPI::None is currently not supported!");
			return nullptr;
			break;
		case RendererAPI::EAPI::OpenGl:
			return new OpenGlIndexBuffer(indices, elementCount);
			break;
		default:
			DM_CORE_ASSERT(false, "{}", "UnKnown RendererAPI!");
			break;
		}
		return nullptr;
	}
}