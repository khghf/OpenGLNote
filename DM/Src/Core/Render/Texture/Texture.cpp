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
		case RendererAPI::EAPI::None:
			DM_CORE_ASSERT(false, "{}", "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::EAPI::OpenGl: return std::make_shared<OpenGlTexture2D>(path);
		}
		DM_CORE_ASSERT(false, "{}", "UnKnown RendererAPI!");
		return nullptr;
		return Ref<Texture2D>();
	}
}

