#pragma once
#include<DataType.h>
class Window;
class GScence;
class Application
{
private:
	UPtr<Window>Win;
	UPtr<GScence>Scence;
private:
	Application();
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
public:
	~Application();
	static Application* GetSingletion();
	void Run();
private:
	void Start();
	void Update(float DeltaTime);
	void OnExit();
};