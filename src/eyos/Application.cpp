#include "eyos/Config.h"
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

template<typename T>
static bool ProcessMessage(T& msg)
{
	g_inputManager->HandleMessage(msg);
	return false;
}

void imguiNewFrame(const eyos::Input& input, const entry::MouseState& mouseState, uint16_t width, uint16_t height);

eyos::RenderableTerrain GenTerrain(std::string path);

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

	RegisterClientEcsTypes(world.ecs);
}

void eyos::Application::Gameloop()
{

}

////////// DEBUG //////////////
static void DrawPerformanceGraphInImgui();
static bool Bar(float _width, float _maxWidth, float _height, const ImVec4& _color);
namespace cmps = eyos::rendering_components;
void FillEcs(eyos::Ecs& ecs, Mesh* mesh, eyos::Material mat);
eyos::RenderableTerrain GenTerrain(std::string path);
void InputTests(const eyos::Input& input);
void ImguiInput(const eyos::Input& input, const entry::MouseState& mouseState);
///////// END DEBUG //////////////


void eyos::Application::Update()
{
//>>>>>>> threaded_ecs
	// create
	Camera camera{};
	camera.position = { 0, 12, 35 };
	camera.rotation = glm::quat{ glm::vec3{0.0, 0.0, 0.0} };
	camera.farZ = setting::camera::farZ;
	camera.fov = setting::camera::fov;
	camera.nearZ = setting::camera::nearZ;
	entry::MouseState mouseState{};
	auto& inputManager = input.inputManager;
	auto& keyboard = input.keyboard;
	auto& mouse = input.mouse;
//<<<<<<< HEAD
	world.time.Initialize(setting::time::maxTimeStep, setting::time::maxSteps);
	std::string path{ setting::terrain::path };
	auto terrain{ std::move((GenTerrain(path))) };
//=======

	// DEBUG STUFF:
	Mesh* bunnyMesh = meshLoad(/*"meshes/Swordsman2.bin"*/ "meshes/Knight.bin");
	Material testMaterial{};
	FillEcs(world.ecs, bunnyMesh, testMaterial);
	auto terrain{ std::move((GenTerrain("../data/maps/"))) };

	world.time.Initialize(0.0333,6);
>>>>>>> threaded_ecs
	while (true)
	{
		inputManager.Update();
		bool shouldExit = entry::processEvents(width, height, renderer.m_debug, renderer.m_reset, &mouseState);
		if (shouldExit)
		{
			break;
		}
		imguiNewFrame(input,mouseState, width, height);
		gen::DrawTerrainToolImgui(path);
		if (path != "")
		{
			terrain = std::move(GenTerrain(path));
		}
		camera.DoMovement(.5f, 0.01f, mouseState);
		renderer.BeginRender(camera);
		renderer.RenderWorld(world.ecs, camera);
		terrain.generatedMesh->submit(0, renderer.GetMeshShaderProgram(), glm::value_ptr(glm::mat4{ 1.0f }), BGFX_STATE_DEFAULT | BGFX_STATE_PT_TRISTRIP);
		renderer.EndRender();
		imguiEndFrame();
		world.time.Update();
	}
}

void eyos::Application::Shutdown()
{
	bool shutdownResult = renderer.Shutdown();
	assertm(shutdownResult, "Failed to shutdown!");
}


eyos::RenderableTerrain GenTerrain(std::string path)
{
	if (path == "../data/maps/" || path == "")
	{
		path = eyos::gen::MapGeneration::GenHeightMap(path);
	}
	if (path != "")
	{
		bimg::ImageContainer* heightmap{ imageLoad(path.c_str(), bgfx::TextureFormat::R8) }; // <--Memory Leak?
		eyos::RenderableTerrain terrain{ static_cast<char*>(heightmap->m_data), heightmap->m_width, heightmap->m_height };
		terrain.GenerateMesh();
		return terrain;
	}
}


void imguiNewFrame(const eyos::Input& input,const entry::MouseState& mouseState, uint16_t width, uint16_t height) {
	imguiBeginFrame(mouseState.m_mx
		, mouseState.m_my
		, (mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
		| (mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
		| (mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
		, mouseState.m_mz
		, width
		, height
	);
	{
		const auto& mouse{ input.mouse };
		const auto& keyboard{ input.keyboard };
		auto& io{ ImGui::GetIO() };

		std::fill_n(io.KeysDown, 512, false);

		io.KeyShift = keyboard->GetBool(gainput::KeyShiftL) | keyboard->GetBool(gainput::KeyShiftR);
		io.KeyCtrl = keyboard->GetBool(gainput::KeyCtrlL) | keyboard->GetBool(gainput::KeyCtrlR);
		io.KeyAlt = keyboard->GetBool(gainput::KeyAltL) | keyboard->GetBool(gainput::KeyAltR);

		std::array<gainput::DeviceButtonSpec, 16> buttons{};
		auto buttonAmount{ keyboard->GetAnyButtonDown(buttons.data(), buttons.size()) };
		for (size_t i{ 0 }; i < buttonAmount; ++i) {
			io.KeysDown[buttons[i].buttonId] = true;
		}

		char c = keyboard->GetNextCharacter();
		while (c != 0) {
			io.AddInputCharacter(c);
			c = keyboard->GetNextCharacter();
		}
	}
}
