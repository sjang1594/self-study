#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace lve
{
	class LveWindow
	{
	public:
		// Constructor
		LveWindow(int w, int h, std::string windowName);
		
		// Copy Constructor (RSII)
		LveWindow(const LveWindow&) = delete;
		// Copy Constructor (RSII)
		LveWindow& operator=(const LveWindow&) = delete;
		
		// Destructor
		~LveWindow();

		bool shouldClose() { return glfwWindowShouldClose(_window); }

	private:
		void InitWindow();
		const int _height;
		const int _width;
		std::string _windowName;
		GLFWwindow* _window;
	};

}

