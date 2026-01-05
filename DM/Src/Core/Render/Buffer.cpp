#include "DMPCH.h"
#include "Buffer.h"
#include"Renderer/Renderer.h"
#include<Core/Log.h>
#include<Platform/Render/OpenGl/Buffer/OpenGlBuffer.h>
namespace DM
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t sizeByte)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::EAPI::None:DM_CORE_ASSERT(false, "{}", "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::EAPI::OpenGl:return std::make_shared<OpenGlVertexBuffer>(sizeByte);
		}
		DM_CORE_ASSERT(false, "{}", "UnKnown RendererAPI!");
		return nullptr;
	}
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t elementCount)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::EAPI::None:DM_CORE_ASSERT(false, "{}", "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::EAPI::OpenGl:return std::make_shared<OpenGlVertexBuffer>(vertices, elementCount);
		}
		DM_CORE_ASSERT(false, "{}", "UnKnown RendererAPI!");
		return nullptr;
	}
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t elementCount)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::EAPI::None:DM_CORE_ASSERT(false, "{}", "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::EAPI::OpenGl:return std::make_shared<OpenGlIndexBuffer>(indices, elementCount);
		}
		DM_CORE_ASSERT(false, "{}", "UnKnown RendererAPI!");
		return nullptr;
	}
}