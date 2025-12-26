//³ÌÐòÈë¿Ú----------------------------------
#include"Platform/EntryPoint.h"
//------------------------------------------
#include<Tool/Imgui/ImguiLayer.h>
#include<imgui.h>
#include<DM.h>
#include<Tool/Util/GameStatic.h>
class ExampleLayer:public DM::Layer
{
public:
	ExampleLayer(std::string_view name) :Layer(name) {}
	virtual ~ExampleLayer() {}
	virtual void OnAttach() 
	{
		std::string vsCode = DM::GameStatic::LoadText("../Assert/Shader/Chunk/Chunk.vs");
		std::string fsCode = DM::GameStatic::LoadText("../Assert/Shader/Chunk/Chunk.fs");
		float vertices[] = {
			-0.5f,0.5f,0.f,		0.f,1.f,
			0.5f,0.5f,0.f,		1.f,1.f,
			0.5f,-0.5f,0.f,		1.f,0.f,
			-0.5f,-0.5f,0.f,	0.f,0.f
		};
		uint32_t indices[] = {
			0,1,2,2,3,0
		};
		float x = DM::Application::GetInst()->GetWindow()->Width();
		float y = DM::Application::GetInst()->GetWindow()->Height();
		Camera = DM::Ref<DM::OrthoGraphicCamera>(new DM::OrthoGraphicCamera(1.f, -1.f, -x / y, x / y));
		//square = DM::Ref<DM::Shader>(DM::Shader::Create(vsCode, fsCode));
		square = DM::Ref<DM::Shader>(DM::Shader::Create("../Assert/Shader/Chunk/Chunk.glsl"));
		VAO = DM::Ref<DM::VertexArray>(DM::VertexArray::Create());
		VBO = DM::Ref<DM::VertexBuffer>(DM::VertexBuffer::Create(vertices, 20));
		IBO = DM::Ref<DM::IndexBuffer>(DM::IndexBuffer::Create(indices,6));
		texture= DM::Ref<DM::Texture2D>(DM::Texture2D::Create("../Assert/Texture/Container/container_diffuse.png"));
		DM::BufferLayout layout = { 
			{DM::ShaderDataType::Float3,"a_Pos"},
			{DM::ShaderDataType::Float2,"a_TexCoord"}
		};
		VBO->SetLayout(layout);
		VAO->AddVertexBuffer(VBO);
		VAO->SetIndexBuffer(IBO);
		square->Bind();
		texture->Bind();
	}
	virtual void OnDetach() {}
	virtual void OnUpdate(float DeltaTime) 
	{
		DM::RenderCommand::SetClearColor({0.1f,1.f,1.f,1.f});
		DM::RenderCommand::Clear();
		DM::Renderer::BeginScene(Camera);
		DM::Renderer::Submit(square, VAO);
		DM::RenderCommand::DrawIndexed(VAO);
		DM::Renderer::EndScene();
	}
	virtual void OnEvent(DM::Event* const e) {}
private:
	DM::Ref<DM::Shader>square;
	DM::Ref<DM::VertexArray>VAO;
	DM::Ref<DM::VertexBuffer>VBO;
	DM::Ref<DM::IndexBuffer>IBO;
	DM::Ref<DM::Texture2D>texture;
	DM::Ref<DM::OrthoGraphicCamera> Camera;
};
class APP :public DM::Application
{
public:
	APP()
	{
		PushLayer(new ExampleLayer("ExampleLayer"));
	}
};
DM::Application* DM::CreateApplication()
{
	return new APP();
}