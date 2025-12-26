#include<DMPCH.h>
#include "Shader.h"
#include"Renderer/Renderer.h"
#include<Platform/Render/OpenGl/OpenGlShader.h>
#include<Tool/Util/GameStatic.h>
namespace DM
{
	Shader::Shader()
	{

	}
	Shader::~Shader()
	{
	}
	Shader* Shader::Create(std::string_view vsCodePath, std::string_view fsCodePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::EAPI::None:
			DM_CORE_ASSERT(false, "{}", "RendererAPI::None is currently not supported!");
			return nullptr;
			break;
		case RendererAPI::EAPI::OpenGl:
			return new OpenGlShader(vsCodePath, fsCodePath);
			break;
		default:
			DM_CORE_ASSERT(false, "{}", "UnKnown RendererAPI!");
			break;
		}
		return nullptr;
	}
	Shader* Shader::Create(std::string_view glslCodePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::EAPI::None:
			DM_CORE_ASSERT(false, "{}", "RendererAPI::None is currently not supported!");
			return nullptr;
			break;
		case RendererAPI::EAPI::OpenGl:
			return new OpenGlShader(glslCodePath);
			break;
		default:
			DM_CORE_ASSERT(false, "{}", "UnKnown RendererAPI!");
			break;
		}
		return nullptr;
	}
}

