#include "EditorLayer.h"
#include<imgui.h>
#include<Core/Math/Vector.h>
#include<Tool/Util/GameStatic.h>
#include<Tool/Util/Util.h>
#include<Tool/Util/TimeMeasurer.h>
#include<Core/Scene/Scene.h>
#include<Core/Scene/Components.h>
#include"Panel/SceneHierarchyPanel.h"
#include"Panel/ContentBrowserPanel.h"
#include <glm/gtc/type_ptr.hpp>
#include<Tool/Util/PlatformUtils.h>
#include"Config.h"


namespace DM
{
	static void BeginDockSpace()
	{
		ImGuiIO& io = ImGui::GetIO();
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static bool opt_opendock = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
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
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)window_flags |= ImGuiWindowFlags_NoBackground;
		if (!opt_padding)ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &opt_opendock, window_flags);
		if (!opt_padding)ImGui::PopStyleVar();
		if (opt_fullscreen)ImGui::PopStyleVar(2);
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
	}
	static void EndDockSpace()
	{
		ImGui::End();
	}




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
		spec.Attachments = { FramebufferTextureFormat::Depth,FramebufferTextureFormat::RGBA8,FramebufferTextureFormat::RED_Int};

		spec.Width =(uint32_t) x;
		spec.Height = (uint32_t)y;


		m_ViewportFramebuffer = FrameBuffer::Create(spec);
		m_HierarchyPanel = CreateRef<SceneHierarchyPanel>(new SceneHierarchyPanel(m_ActiveScene));
		m_ContentPanel = CreateRef<ContentBrowserPanel>(new ContentBrowserPanel(m_ActiveScene));
	}

	void EditorLayer::OnDetach()
	{
		__super::OnDetach();
		DM::Renderer2D::ShoutDown();
		if (m_ActiveScene)
		{
			SceneSerializer::Serialize(m_ActiveScene);
		}
	}

	void EditorLayer::OnUpdate(float DeltaTime)
	{
		PROFILE_SCOPE();
		m_ViewportFramebuffer->Bind();
		DM::RenderCommand::Clear();
		m_ViewportFramebuffer->ClearColorAttachment(1, -2);
		if (m_ActiveScene)
		{
			auto& group = m_ActiveScene->m_Registry.group<SpriteComponent, TransformComponent>();
			if (m_ViewPort.bHovered)m_CameraController.OnUpdate(DeltaTime);
			DM::Renderer2D::BeginScene(m_CameraController.GetCamera());
			for (auto& entity : group)
			{
				auto& [sprite, transform] = group.get<SpriteComponent, TransformComponent>(entity);
				DM::Renderer2D::DrawQuad(sprite, transform);
			}
			DM::Renderer2D::EndScene();
		}
		//int pixelData = m_ViewportFramebuffer->ReadPixel(1, (int)m_ViewPort.MousePosLocal.x,(int)m_ViewPort.MousePosLocal.y);
		
		//LOG_CORE_INFO("pixelData:{}", pixelData);

		m_ViewportFramebuffer->UnBind();
	}

	void EditorLayer::OnEvent(Event* const e)
	{
		m_CameraController.OnEvent(e);
	}

	void EditorLayer::Render()
	{
		BeginDockSpace();
		{
			RenderMenuBar();//渲染菜单栏
			RenderViewPort();//渲染视口
			RenderSetting();
			m_HierarchyPanel->Render();//渲染层级面板
			m_ContentPanel->Render();
		}
		EndDockSpace();
	}

	void EditorLayer::UpdateEditor()
	{

	}

	void EditorLayer::UpdateRunTime()
	{

	}

	void EditorLayer::OnSceneChanged()
	{
		m_HierarchyPanel->SetContext(m_ActiveScene);
	}

	void EditorLayer::RenderViewPort()
	{
		ImGui::Begin("ViewPort", 0, ImGuiWindowFlags_NoTitleBar);
		{
			ImGuiStyle& style = ImGui::GetStyle();
			m_ViewPort.bHovered = ImGui::IsWindowHovered();
			m_ViewPort.bFocused = ImGui::IsWindowFocused();
			Application::GetInst()->BlockEvent(!m_ViewPort.bHovered);
			Vector2 viewportPanelSize;
			ImVec2 imvec = ImGui::GetContentRegionAvail();
			
			viewportPanelSize.x = imvec.x;
			viewportPanelSize.y = imvec.y;
			if (m_ViewPort.Size != viewportPanelSize)
			{
				m_ViewPort.Size = viewportPanelSize;
				m_ViewportFramebuffer->Resize((uint32_t)m_ViewPort.Size.x, (uint32_t)m_ViewPort.Size.y);
				RenderCommand::SetViewport((uint32_t)m_ViewPort.Size.x, (uint32_t)m_ViewPort.Size.y);
				m_CameraController.SetProjection(m_ViewPort.Size.x / m_ViewPort.Size.y);
			}
			uint32_t id = m_ViewportFramebuffer->GetColorAttachmentId();
			ImTextureRef textureRef((void*)id);
			ImGui::Image(textureRef, imvec, { 0,1 }, { 1,0 });
			if (m_ViewPort.bFocused&& m_ViewPort.bHovered)
			{
				ImVec2 screenPos = ImGui::GetCursorScreenPos();
				m_ViewPort.MinBound.x = screenPos.x;
				m_ViewPort.MinBound.y = screenPos.y - style.WindowPadding.y / 2.f;
				m_ViewPort.MaxBound = m_ViewPort.MinBound + m_ViewPort.Size;
				ImVec2 mousePos = ImGui::GetMousePos();
				m_ViewPort.MousePosScreen.x = mousePos.x;
				m_ViewPort.MousePosScreen.y = mousePos.y;
				m_ViewPort.MousePosLocal.x = mousePos.x - m_ViewPort.MinBound.x;
				m_ViewPort.MousePosLocal.y = m_ViewPort.MinBound.y - mousePos.y;
				m_ViewPort.MousePosLocalNarmal = m_ViewPort.MousePosLocal / m_ViewPort.Size;
			}
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_DRAG_ITEM"))
				{
					const wchar_t* data = static_cast<const wchar_t*>(payload->Data);
					OpenScene(data);
				}
				ImGui::EndDragDropTarget();
			}

			//LOG_CORE_INFO("1:{},2:{}", style.WindowPadding.x, style.WindowPadding.y);
		}
		ImGui::End();//ViewPort
	}

	void EditorLayer::RenderSetting()
	{
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
			ImGui::SeparatorText("ViewPort");

			ImGui::Text("MinBoundX:%f", m_ViewPort.MinBound.x);
			ImGui::Text("MinBoundY:%f", m_ViewPort.MinBound.y);
			ImGui::Text("MaxBoundX:%f", m_ViewPort.MaxBound.x);
			ImGui::Text("MaxBoundY:%f", m_ViewPort.MaxBound.y);
			ImGui::Text("ViewPortSizeX:%f", m_ViewPort.Size.x);
			ImGui::Text("ViewPortSizeY:%f", m_ViewPort.Size.y);
			ImGui::Text("MousePosLocal_X:%f", m_ViewPort.MousePosLocal.x);
			ImGui::Text("MousePosLocal_Y:%f", m_ViewPort.MousePosLocal.y);
			ImGui::Text("MousePosScreen_X:%f", m_ViewPort.MousePosScreen.x);
			ImGui::Text("MousePosScreen_Y:%f", m_ViewPort.MousePosScreen.y);
			ImGui::Text("MousePosLocalNarmalX:%f", m_ViewPort.MousePosLocalNarmal.x);
			ImGui::Text("MousePosLocalNarmalY:%f", m_ViewPort.MousePosLocalNarmal.y);
		}
		ImGui::End();//Setting
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
				if (m_ActiveScene)
				{
					SceneSerializer::Serialize(m_ActiveScene);
				}
				m_ActiveScene.reset(new Scene());
				OnSceneChanged();
			}
			if (ImGui::MenuItem("OpenScene","Ctrl+O"))
			{
				std::string path = FileDialog::OpenFile();
				OpenScene(path);
			}
			if (ImGui::MenuItem("SaveScene", "Ctrl+S",nullptr,m_ActiveScene.get()!=nullptr))
			{
				std::string path = FileDialog::SaveFile(m_ActiveScene->m_Name.c_str());
				if (!path.empty())
				{
					m_ActiveScene->m_path = path+"."+ m_ActiveScene->s_FileExtension.data();
					SceneSerializer::Serialize(m_ActiveScene);
				}
			}
			if (ImGui::MenuItem("Exit"))
			{
				Application::GetInst()->Close();
			}
			ImGui::EndMenu();
		}
	}

	void EditorLayer::OpenScene(std::filesystem::path p)
	{
		
		if (std::filesystem::is_regular_file(p)&&Util::HasSuffix(p.string(),Scene::s_FileExtension.data()))
		{
			if (m_ActiveScene)
			{
				SceneSerializer::Serialize(m_ActiveScene);
				m_ActiveScene.reset();
			}
			m_ActiveScene=SceneSerializer::DeSerialize(p.string());
			DM_CORE_ASSERT(m_ActiveScene, "Open scene failed path:{}", p.string());
			OnSceneChanged();
			LOG_CORE_INFO("OpenScene:{}", p.string());
		}
	}

}

