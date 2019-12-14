#include <iostream>
#include <memory>

#include "bgfx_utils.h"
#include <entry\entry.h>
#include <imgui\imgui.h>

#include "eyos/rendering/EyosRenderer.h"
#include "engine/ecs/Ecs.h"
#include "eyos/rendering/Components.h"

namespace cmps = eyos::rendering_components;

static void WaitForEnter()
{
	std::cout << "Press enter to exit...\n";
	std::cin.get();
}

int _main_(int _argc, char** _argv)
{
	std::cout << "Hello CMake & BGFX :)\n";

	uint32_t width = 1280;
	uint32_t height = 720;

	eyos::Ecs<cmps::Transform, cmps::Model3D> ecs{};

	entry::MouseState mouseState;
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
		bool shouldExit = entry::processEvents(width, height, renderer->m_debug, renderer->m_reset, &mouseState);
		if (shouldExit)
		{
			break;
		}
		imguiBeginFrame(mouseState.m_mx
			, mouseState.m_my
			, (mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
			| (mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
			| (mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
			, mouseState.m_mz
			, uint16_t(width)
			, uint16_t(height)
		);

		renderer->Render();
	}

	if (!renderer->Shutdown()) {
		std::cerr << "Failed to shutdown!" << std::endl;
		return 2;
	}

	return 0;
}
