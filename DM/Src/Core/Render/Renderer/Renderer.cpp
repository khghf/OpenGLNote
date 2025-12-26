#include<DMPCH.h>
#include"Renderer.h"
#include<Platform/Render/OpenGl/OpenGlShader.h>
namespace DM
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();
	void Renderer::Init()
	{
		RenderCommand::Init();
	}
	void Renderer::BeginScene(const Ref<OrthoGraphicCamera>& orthoCamera)
	{
		m_SceneData->ProjectionViewMartix = orthoCamera->GetProjectionViewMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray)
	{
		shader->Bind();
		vertexArray->Bind();
		Ref<OpenGlShader>openglShader=std::dynamic_pointer_cast<OpenGlShader>(shader);
		openglShader->UploadMat4x4("u_ProjectionViewMatrix", m_SceneData->ProjectionViewMartix);
		openglShader->UploadMat4x4("u_ModelMatrix", m_SceneData->ModelMartix);
		openglShader->UploadInt("u_Texture", 0);
		RenderCommand::DrawIndexed(vertexArray);
	}
	RendererAPI::EAPI Renderer::GetAPI() { return RendererAPI::GetAPI(); }
}