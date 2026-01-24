#include<Window.h>
Window::~Window()
{
	if (GlfwWin != nullptr) 
	{
		glfwDestroyWindow(GlfwWin); // 销毁窗口
	}
	glfwTerminate(); // 终止 GLFW
	std::cout << "~Window" << std::endl;

}
GLFWwindow* const Window::GetGlfwWindow() const
{
	return GlfwWin;
}

bool Window::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GlfwWin = glfwCreateWindow(Width, Height, Title.c_str(), nullptr, nullptr);
	//glViewport(0, 0, Width, Height);
	if (GlfwWin == nullptr)
	{
		std::cerr << "Failed to Create GLFW Window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(GlfwWin);
	glfwSetInputMode(GlfwWin, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD function pointer" << std::endl;
		glfwTerminate();
		return false;
	}
	return true;
}
