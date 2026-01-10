#include "EditorLayer.h"
#include<imgui.h>
#include<Core/Math/Vector.h>
#include<Tool/Util/GameStatic.h>
#include<Tool/Util/TimeMeasurer.h>
#include<Core/Scene/Scene.h>
#include<Core/Scene/Components.h>
#include"Panel/SceneHierarchyPanel.h"
#include <glm/gtc/type_ptr.hpp>
#include<Tool/Util/PlatformUtils.h>
namespace DM
{
	EditorLayer::EditorLayer(const std::string_view& name) :ImGuiLayer(name)
	{
		
	}

	EditorLayer::~EditorLayer()
	{

	}

	void EditorLayer::OnAttach()
	{
		__super::OnAttach();
		DM::Renderer2D::Init();
		float x = (float)DM::Application::GetInst()->GetWindow()->Width();
		float y = (float)DM::Application::GetInst()->GetWindow()->Height();
		m_CameraController = CameraController(x / y, ECameraType::Ortho);
		FrameBufferSpecification spec;
		spec.Width =(uint32_t) x;
		spec.Height = (uint32_t)y;
		m_ViewportFramebuffer = FrameBuffer::Create(spec);
		//m_ActiveScene = CreateRef<Scene>(new Scene());
		m_Panel = CreateRef<SceneHierarchyPanel>(new SceneHierarchyPanel(m_ActiveScene));
		m_SceneSerializer = SceneSerializer(m_ActiveScene);
		//m_SceneSerializer.DeSerialize("Assert/Save/Save.scene");
	}

	void EditorLayer::OnDetach()
	{
		__super::OnDetach();
		DM::Renderer2D::ShoutDown();
		m_SceneSerializer.Serialize("Assert/Save/Save.scene");
	}

	void EditorLayer::OnUpdate(float DeltaTime)
	{
		PROFILE_SCOPE();
		m_ViewportFramebuffer->Bind();
		DM::RenderCommand::Clear();

		//DM::Renderer2D::DrawQuad({ -1.5f,-1.5f,0.f }, { 1.f,1.f }, { 1.f,0.f,0.f,1.5f });//red
		//DM::Renderer2D::DrawQuad({ 0.5f,0.5f,0.f }, { 1.f,1.f }, { 0.f,1.f,0.f,1.5f });//green container_specular

		//DM::Renderer2D::DrawQuad({ 0.f,0.f,-0.3f }, { 20.f,20.f }, GameStatic::GetTexture2D("container_diffuse"), {20,20});//green
		////DM::Renderer2D::DrawQuad({ -2.f,-2.f,-0.f }, { 2.f,2.f }, GameStatic::GetTexture2D("container_specular"));//green
		if (m_ActiveScene)
		{
			auto& group = m_ActiveScene->m_Registry.group<SpriteComponent, TransformComponent>();
			if (m_bViewportHovered)m_CameraController.OnUpdate(DeltaTime);
			DM::Renderer2D::BeginScene(m_CameraController.GetCamera());
			for (auto& entity : group)
			{
				auto& [sprite, transform] = group.get<SpriteComponent, TransformComponent>(entity);
				DM::Renderer2D::DrawQuad(sprite, transform);
			}
			DM::Renderer2D::EndScene();
		}
		m_ViewportFramebuffer->UnBind();
	}

	void EditorLayer::OnEvent(Event* const e)
	{
		m_CameraController.OnEvent(e);
	}

	void EditorLayer::Render()
	{
		
		ImGuiIO& io = ImGui::GetIO();
		// TL;DR; this demo is more complicated than what most users you would normally use.
	// If we remove all options we are showcasing, this demo would become a simple call to ImGui::DockSpaceOverViewport() !!
	// In this specific demo, we are not using DockSpaceOverViewport() because:

		static bool opt_fullscreen = true;
		//static bool opt_fullscreen = false;
		static bool opt_padding = false;
		static bool opt_opendock = true;

		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &opt_opendock, window_flags);
		{
			if (!opt_padding)ImGui::PopStyleVar();
			if (opt_fullscreen)ImGui::PopStyleVar(2);
			// Submit the DockSpace
			// REMINDER: THIS IS A DEMO FOR ADVANCED USAGE OF DockSpace()!
			// MOST REGULAR APPLICATIONS WILL SIMPLY WANT TO CALL DockSpaceOverViewport(). READ COMMENTS ABOVE.
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}
			// Show demo options and help
			RenderMenuBar();
			ImGui::Begin("ViewPort", 0, ImGuiWindowFlags_NoTitleBar);
			{
				m_bViewportHovered = ImGui::IsWindowHovered();
				m_bViewportFocused = ImGui::IsWindowFocused();
				Application::GetInst()->BlockEvent(!m_bViewportHovered);
				Vector2 viewportPanelSize;
				ImVec2 imvec = ImGui::GetContentRegionAvail();
				viewportPanelSize.x = imvec.x;
				viewportPanelSize.y = imvec.y;
				if (m_ViewportSize != viewportPanelSize)
				{
					m_ViewportSize = viewportPanelSize;
					m_ViewportFramebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
					RenderCommand::SetViewport((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
					m_CameraController.SetProjection(m_ViewportSize.x / m_ViewportSize.y);
				}
				uint32_t id = m_ViewportFramebuffer->GetColorAttachmentId();
				ImTextureRef textureRef((void*)id);
				ImGui::Image(textureRef, imvec, { 0,1 }, { 1,0 });
			}
			ImGui::End();//ViewPort
			ImGui::Begin("Setting");
			{

				ImGui::SeparatorText("Render");
				ImGui::Text("DrawCall:%d", Renderer2D::GetStats().DrawCall);
				ImGui::Text("QuadCount:%d", Renderer2D::GetStats().QuadCount);
				ImGui::Text("VertexCount:%d", Renderer2D::GetStats().GetVertexCount());
				ImGui::Text("IndexCount:%d", Renderer2D::GetStats().GetIndexCount());
				ImGui::SeparatorText("CameraController");
				ImGui::SliderFloat("MoveSensitivity", &m_CameraController.m_MoveSensitivity, 1.f, 100.f);
				ImGui::SliderFloat("ZoomSensitivity", &m_CameraController.m_ZoomSensitivity, 1.f, 100.f);
			}
			ImGui::End();//Setting
			m_Panel->OnUIRender();
		}
		ImGui::End();
		
	}

	void EditorLayer::OnSceneChanged()
	{
		m_Panel->SetContext(m_ActiveScene);
		m_SceneSerializer.SetContext(m_ActiveScene);
	}

	void EditorLayer::RenderMenuBar()
	{
		if (ImGui::BeginMenuBar())
		{
			RenderMenuBar_File();
			ImGui::EndMenuBar();
		}
	}

	void EditorLayer::RenderMenuBar_File()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("NewScene"))
			{
				m_SceneSerializer.Serialize("Assert/Save/Save.scene");
				m_ActiveScene.reset();
				OnSceneChanged();
			}
			if (ImGui::MenuItem("OpenScene"))
			{
				std::string path = FileDialog::OpenFile();
				if (!path.empty())
				{
					m_ActiveScene.reset(new Scene());
					OnSceneChanged();
					LOG_CORE_INFO("OpenScene:{}", path);
					m_SceneSerializer.DeSerialize(path);
				}
				
			}
			if (ImGui::MenuItem("SaveScene"))
			{
				std::string path = FileDialog::OpenFile();
				if (!path.empty())
				{
					m_SceneSerializer.Serialize(path);
				}
			}
			if (ImGui::MenuItem("Exit"))
			{
				Application::GetInst()->Close();
			}

			ImGui::EndMenu();
		}
	}

}

