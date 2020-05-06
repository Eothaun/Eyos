#include "eyos/Application.h"
#include "eyos/rendering/Camera.h"

#include "bgfx_utils.h"
#include "eyos/rendering/Components.h"
#include "eyos/rendering/Camera.h"
#include "eyos/rendering/RenderableTerrain.h"
#include "eyos/rendering/Material.h"

//DEBUG IMGUI
#include "eyos/ui/DebugTerrainUI.h"
///

#include "engine/gen/MapGeneration.h"
#include "engine/ecs/EntityId.h"

#include <entry/entry_p.h>
#include <imgui/imgui.h>
#include <bimg/decode.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <array>

/*
* \important life time of this object is bound to the Application class because it holds the input struct
*/
static gainput::InputManager* g_inputManager{ nullptr };


void imguiNewFrame(const entry::MouseState& mouseState, uint16_t width, uint16_t height);

template<typename T>
static bool ProcessMessage(T& msg)
{
	g_inputManager->HandleMessage(msg);
	return false;
}

void eyos::Application::Init(int _argc, char** _argv)
{
	assertm(renderer.Init(_argc, _argv, width, height), "Failed to initialize the renderer!!");
	bgfx::frame();
	entry::setWindowSize(windowHandle, width, height);
	input.Init(width, height);
	g_inputManager = &input.inputManager;
#if BX_PLATFORM_WINDOWS
		entry::SetNativeMessageCallback(&ProcessMessage<MSG>); 
#elif BX_PLATFORM_BSD || BX_PLATFORM_LINUX || BX_PLATFORM_RPI
		entry::SetNativeMessageCallback(&ProcessMessage<XEvent>);//FIXME: why does this not work under Linux?
#endif
}

void eyos::Application::Gameloop()
{
	// create
	Camera camera{};
	camera.position = { 0, 12, 35 };
	camera.rotation = glm::quat{ glm::vec3{0.0, 0.0, 0.0} };
	entry::MouseState mouseState{};
	auto& inputManager = input.inputManager;
	auto& keyboard = input.keyboard;
	auto& mouse = input.mouse;
	world.time.Initialize(0.0333,6);
	while (true)
	{
		inputManager.Update();
		bool shouldExit = entry::processEvents(width, height, renderer.m_debug, renderer.m_reset, &mouseState);
		if (shouldExit)
		{
			break;
		}
		imguiNewFrame(mouseState, width, height);
		camera.DoMovement(.5f, 0.01f, mouseState);
		renderer.BeginRender(camera);
		renderer.RenderWorld(world.esc, camera);
		renderer.EndRender();
		imguiEndFrame();
		world.time.Update();
	}
}

void eyos::Application::Shutdown()
{
	assertm(renderer.Shutdown(), "Failed to shutdown!");
}


void imguiNewFrame(const entry::MouseState& mouseState, uint16_t width, uint16_t height) {
	imguiBeginFrame(mouseState.m_mx
		, mouseState.m_my
		, (mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
		| (mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
		| (mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
		, mouseState.m_mz
		, width
		, height
	);
}