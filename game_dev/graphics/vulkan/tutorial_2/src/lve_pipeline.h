#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace lve {
	class Lve_Pipeline
	{
	public:
		Lve_Pipeline(const std::string& vertFilepath, const std::string& fragFilepath);
	private:
		static std::vector<char> readFile(const std::string& filepath);
		void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath);
	};

}

