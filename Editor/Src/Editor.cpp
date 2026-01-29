//程序入口----------------------------------
#include"Platform/EntryPoint.h"
//------------------------------------------
#include<Tool/Imgui/ImguiLayer.h>
#include<imgui.h>
#include<DM.h>
#include<Tool/Util/GameStatic.h>
#include<Core/Render/Camera/CameraController.h>
#include"EditorLayer.h"
namespace DM
{
	class Editor :public GEngine
	{
	public:
		Editor()
		{
			PushOverLayer(new EditorLayer("EditorLayer"));
		}
	};
	GEngine* CreateApplication()
	{
		return new Editor();
	}
}
