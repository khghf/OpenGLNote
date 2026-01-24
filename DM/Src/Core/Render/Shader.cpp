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
	Ref<Shader> Shader::Create(const std::string_view& glslCodePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::EAPI::None:DM_CORE_ASSERT(false, "{}", "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::EAPI::OpenGl:return std::make_shared<OpenGlShader>(glslCodePath); break;
		}
		DM_CORE_ASSERT(false, "{}", "UnKnown RendererAPI!");
		return Ref<Shader>();
	}
}

