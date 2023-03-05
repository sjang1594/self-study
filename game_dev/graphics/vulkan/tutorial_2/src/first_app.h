#pragma once

#include "lve_window.h"
#include "lve_pipeline.h"

namespace lve {
	class FirstApp
	{
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 800;

		void run();

	private:
		LveWindow lveWindow{WIDTH, HEIGHT, "Hello Vulkan"};
		Lve_Pipeline lvePipeline{ "shaders/simple_vs.vert.spv", "shaders/simple_fs.frag.spv" };
	};
}

