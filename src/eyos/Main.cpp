#include <iostream>
#include <memory>

#include "bgfx_utils.h"
#include <entry\entry.h>

#include "eyos/rendering/EyosRenderer.h"

static void WaitForEnter()
{
	std::cout << "Press enter to exit...\n";
	std::cin.get();
}

int _main_(int _argc, char** _argv)
{
	std::cout << "Hello CMake & BGFX :)\n";

	int width = 1280;
	int height = 720;

	std::unique_ptr<eyos::Renderer> renderer{ new eyos::Renderer() };
	if (!renderer->Init(_argc, _argv, width, height)) {
		std::cerr << "Failed to initialize!" << std::endl;
		return 1;
	}
	bgfx::frame();

	entry::WindowHandle defaultWindow = { 0 };
	setWindowSize(defaultWindow, width, height);

	while (true)
	{
		renderer->Render();
	}

	if (!renderer->Shutdown()) {
		std::cerr << "Failed to shutdown!" << std::endl;
		return 2;
	}

	WaitForEnter();

	return 0;
}
