//程序入口----------------------------------
#include"Platform/EntryPoint.h"
//------------------------------------------
#include<Tool/Imgui/ImguiLayer.h>
#include<imgui.h>
#include<DM.h>
#include<Tool/Util/GameStatic.h>
#include<Core/Render/Camera/CameraController.h>
#include"Renderer2DExample.h"
class ExampleLayer:public DM::Layer
{
public:
	ExampleLayer(std::string_view name) :Layer(name) {}
	virtual ~ExampleLayer() {}
	virtual void OnAttach() 
	{
		float vertices[] = {
			-0.5f,0.5f,0.f,		0.f,1.f,
			0.5f,0.5f,0.f,		1.f,1.f,
			0.5f,-0.5f,0.f,		1.f,0.f,
			-0.5f,-0.5f,0.f,	0.f,0.f
		};
		uint32_t indices[] = {
			0,1,2,2,3,0
		};
		float x = (float)DM::Application::GetInst()->GetWindow()->Width();
		float y = (float)DM::Application::GetInst()->GetWindow()->Height();
		m_CameraController = DM::CameraController(x/y,DM::ECameraType::Ortho);

		square = DM::GameStatic::GetShader("Chunk");
		texture = DM::GameStatic::GetTexture2D("container_diffuse");
		VAO = DM::VertexArray::Create();
		VBO = DM::VertexBuffer::Create(vertices, 20);
		IBO = DM::IndexBuffer::Create(indices,6);
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
		/*m_CameraController.OnUpdate(DeltaTime);
		DM::RenderCommand::SetClearColor({0.1f,1.f,1.f,1.f});
		DM::RenderCommand::Clear();
		DM::Renderer::BeginScene(m_CameraController.GetCamera());
		DM::Renderer::Submit(square, VAO);
		DM::Renderer::EndScene();*/
	}
	virtual void OnEvent(DM::Event* const e) {}
private:
	DM::Ref<DM::Shader>square;
	DM::Ref<DM::VertexArray>VAO;
	DM::Ref<DM::VertexBuffer>VBO;
	DM::Ref<DM::IndexBuffer>IBO;
	DM::Ref<DM::Texture2D>texture;
	DM::CameraController m_CameraController;
};
class APP :public DM::Application
{
public:
	APP()
	{
		//PushLayer(new Renderer2DExample("Renderer2DExample"));
	}
};
DM::Application* DM::CreateApplication()
{
	return new APP();
}