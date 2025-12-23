//³ÌÐòÈë¿Ú----------------------------------
#include"Platform/EntryPoint.h"
//------------------------------------------
#include<Tool/Imgui/ImguiLayer.h>
#include<imgui.h>
class APP :public DM::Application
{
public:
	APP()
	{
	}

};
DM::Application* DM::CreateApplication()
{
	return new APP();
}