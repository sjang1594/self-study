#include "first_app.h"

namespace lve
{
	void lve::FirstApp::run()
	{

		while (!lveWindow.shouldClose())
		{
			glfwPollEvents();
		}
	}
} // namespace lve
