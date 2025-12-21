//³ÌÐòÈë¿Ú----------------------------------
#include"Platform/EntryPoint.h"
//------------------------------------------
#include<Tool/Imgui/ImguiLayer.h>
class APP :public DM::Application
{
public:
	APP()
	{
		//m_LayerStack->PushOverlay(new DM::ImguiLayer());
	}

};
DM::Application* DM::CreateApplication()
{
	return new APP();
}