#pragma once
#include<Core/Layer/Layer.h>
#include<Core/Render/Camera/CameraController.h>
#include<GEngine.h>
#include<Core/Render/Renderer/Renderer2D.h>
#include<Resource/AssetManager.h>
#include<Core/Render/Texture/Texture.h>
#include<Tool/Util/TimeMeasurer.h>

class Renderer2DExample :public DM::Layer
{
public:
	Renderer2DExample(const std::string_view&name) :Layer(name)
	{
		float x = (float)DM::GEngine::GetInst()->GetWindow()->Width();
		float y = (float)DM::GEngine::GetInst()->GetWindow()->Height();
		m_CameraController = DM::CameraController(x / y, DM::ECameraType::Ortho);
	}
	virtual ~Renderer2DExample() {}
	virtual void OnAttach() 
	{
		DM::Renderer2D::Init();
	}
	virtual void OnDetach() 
	{
		DM::Renderer2D::ShoutDown();
	}
	virtual void OnUpdate(float DeltaTime) 
	{
		PROFILE_SCOPE();
		m_CameraController.OnUpdate(DeltaTime);
		DM::RenderCommand::Clear();
		//DM::Renderer2D::BeginScene(m_CameraController.GetCamera());
		//DM::Renderer2D::DrawQuad({ -1.5f,-1.5f,-0.5f }, { 1.f,1.f }, { 1.f,0.f,0.f,1.5f });//red
		//DM::Renderer2D::DrawQuad({ 0.5f,0.5f,0.f }, { 1.f,1.f }, { 0.f,1.f,0.f,1.5f });//green container_specular

		//DM::Renderer2D::DrawQuad({ 0.f,0.f,-0.f }, { 2.f,2.f }, DM::AssetManager::GetInst()->GetAsset<DM::Texture2D>("container_diffuse"));//green
		//DM::Renderer2D::DrawQuad({ -2.f,-2.f,-0.f }, { 2.f,2.f }, DM::AssetManager::GetInst()->GetAsset<DM::Texture2D>("container_specular"));//green
		//DM::Renderer2D::EndScene();
	}
	virtual void OnEvent(DM::Event* const e) {
		//m_CameraController.OnEvent(e);
	}
private:
	DM::CameraController m_CameraController;
};