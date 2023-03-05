#include "lve_window.h"

namespace lve
{
	LveWindow::LveWindow(int w, int h, std::string windowName) : _width{w}, _height{h}, _windowName{windowName}
	{
		InitWindow();
	}

	LveWindow::~LveWindow()
	{
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

	void LveWindow::InitWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		_window = glfwCreateWindow(_width, _height, _windowName.c_str(), nullptr, nullptr);
	}

} // namespace lve
