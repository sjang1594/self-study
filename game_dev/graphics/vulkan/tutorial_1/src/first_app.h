#pragma once

#include "lve_window.h"

namespace lve {
	class FirstApp
	{
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 800;

		void run();

	private:
		LveWindow lveWindow{WIDTH, HEIGHT, "Hello Vulkan"};
	};
}

