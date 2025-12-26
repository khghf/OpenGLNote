#include "DMPCH.h"
#include<Platform/Render/OpenGl/Renderer/OpenGlRendererAPI.h>
#include "RenderCommand.h"
namespace DM
{
	RendererAPI* RenderCommand::s_API = new OpenGlRendererAPI();
	
}
