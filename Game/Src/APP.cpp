//³ÌÐòÈë¿Ú----------------------------------
#include"Platform/EntryPoint.h"
//------------------------------------------
class APP :public DM::Application
{
public:
	APP() = default;
};
DM::Application* DM::CreateApplication()
{
	static APP* App = nullptr;
	if (App == nullptr)
	{
		App = new APP();
	}
	return App;
}