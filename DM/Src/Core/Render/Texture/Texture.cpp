#include<DMPCH.h>
#include "Texture.h"
#include"../Renderer/Renderer.h"
#include<Platform/Render/OpenGl/Texture/OpenGlTexture.h>
namespace DM
{
	Ref<Texture2D> Texture2D::Create( const std::string_view& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::EAPI::None:DM_CORE_ASSERT(false, "{}", "RendererAPI::None is currently not supported!");return nullptr;
		case RendererAPI::EAPI::OpenGl: return CreateRef<OpenGlTexture2D>(path);
		}
		DM_CORE_ASSERT(false, "{}", "UnKnown RendererAPI!");
		return Ref<Texture2D>();
	}
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::EAPI::None:DM_CORE_ASSERT(false, "{}", "RendererAPI::None is currently not supported!");return nullptr;
		case RendererAPI::EAPI::OpenGl: return CreateRef<OpenGlTexture2D>(width,height);
		}
		DM_CORE_ASSERT(false, "{}", "UnKnown RendererAPI!");
		return Ref<Texture2D>();
	}
}

