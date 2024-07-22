#include <iostream>
#include <memory>
#include <Windows.h>

#include "LunaEngineApp.h"

int main() {
    LunaEngine::LunaEngineApp app;

	if (!app.Initialize())
	{
        std::cout << "FAILED: Init" << std::endl;
        return -1;
	}
    return app.Run();
}