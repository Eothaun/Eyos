#include <iostream>
#include <memory>

#include "bgfx_utils.h"
#include <entry\entry.h>
#include <imgui\imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine/ecs/EntityId.h"
#include "eyos/rendering/EyosRenderer.h"
#include "eyos/ClientEcsType.h"
#include "eyos/rendering/Components.h"
#include "eyos/rendering/Camera.h"
#include "eyos/rendering/RenderableTerrain.h"

namespace cmps = eyos::rendering_components;

static void WaitForEnter()
{
	std::cout << "Press enter to exit...\n";
	std::cin.get();
}

int _main_(int _argc, char** _argv)
{
	using namespace eyos;

	std::cout << "Hello CMake & BGFX :)\n";

	uint32_t width = 1280;
	uint32_t height = 720;


	entry::MouseState mouseState;
	std::unique_ptr<eyos::Renderer> renderer{ new eyos::Renderer() };
	if (!renderer->Init(_argc, _argv, width, height)) {
		std::cerr << "Failed to initialize!" << std::endl;
		return 1;
	}
	bgfx::frame();

	entry::WindowHandle defaultWindow = { 0 };
	setWindowSize(defaultWindow, width, height);


	EyosEcs ecs{};

	// Fill ecs for testing
	Mesh* bunnyMesh = meshLoad("meshes/Swordsman2.bin");
	Material testMaterial{};
	{
		EntityId model = ecs.CreateEntity();
		ecs.Assign(model, cmps::Transform{ glm::vec3{0, 0, 0}, glm::quat{ glm::vec3{} } });
		ecs.Assign(model, cmps::Model3D{ bunnyMesh, &testMaterial });
	}
	{
		EntityId model = ecs.CreateEntity();
		ecs.Assign(model, cmps::Transform{ glm::vec3{25, 0, 0}, glm::quat{ glm::vec3{-3.14 / 2, 0, 0} }, glm::vec3{ 0.25f } });
		ecs.Assign(model, cmps::Model3D{ bunnyMesh, &testMaterial });
	}

	std::cout << EntityId{ 420, 69 };
	
	bimg::ImageContainer* heightmap = imageLoad("maps/heightmap.png", bgfx::TextureFormat::R8);
	RenderableTerrain terrain{ static_cast<char*>(heightmap->m_data), heightmap->m_width, heightmap->m_height };
	terrain.GenerateMesh();


	Camera camera{};
	camera.position = { 0, 12, 35 };
	camera.rotation = glm::quat{ glm::vec3{0.0, 0.0, 0.0} };

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

		ImGui::Begin("EyosRenderer ImGUI");
		ImGui::Text("%s", "EyosRenderer Imgui Test");
		ImGui::End();

		camera.DoFreecamMovement(0.5f, 0.01f, mouseState);

		imguiEndFrame();
		renderer->BeginRender(camera);
		renderer->RenderWorld(ecs, camera);
		terrain.generatedMesh->submit(0, renderer->GetMeshShaderProgram(), glm::value_ptr(glm::mat4{ 1.0f }), BGFX_STATE_DEFAULT | BGFX_STATE_PT_TRISTRIP);
		renderer->EndRender();
	}

	if (!renderer->Shutdown()) {
		std::cerr << "Failed to shutdown!" << std::endl;
		return 2;
	}

	return 0;
}
