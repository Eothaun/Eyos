#include <iostream>
#include <memory>
#include <filesystem>
#include <array>

#include "bgfx_utils.h"
#include <entry/entry_p.h>
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <gainput/gainput.h>

#include "engine/ecs/EntityId.h"
#include "eyos/rendering/EyosRenderer.h"
#include "eyos/ClientEcsType.h"
#include "eyos/rendering/Components.h"
#include "eyos/rendering/Camera.h"
#include "eyos/rendering/RenderableTerrain.h"

#include "engine/gen/PerlinNoise.h"
#include "engine/gen/Image.h"
#include <sstream>
#include <bimg/decode.h>

//!!!!!!!!!!!!
//!!! NOTE !!!	THESE INCLUDES ARE AT THE BOTTOM BECAUSE OF MACRO REASONS, DON"T ADD #include s BELOW HERE!!!
//!!!!!!!!!!!!
#if ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_WINDOWS
#include <windows.h>
#elif ENTRY_CONFIG_USE_NATIVE && (BX_PLATFORM_BSD || BX_PLATFORM_LINUX || BX_PLATFORM_RPI)
#include <X11/Xlib.h> // will include X11 which #defines None... Don't mess with order of includes.
#endif

namespace cmps = eyos::rendering_components;

static void WaitForEnter()
{
	std::cout << "Press enter to exit...\n";
	std::cin.get();
}

#pragma region Taken from: example-glue.cpp
struct SampleData
{
	static constexpr uint32_t kNumSamples = 100;

	SampleData()
	{
		reset();
	}

	void reset()
	{
		m_offset = 0;
		bx::memSet(m_values, 0, sizeof(m_values));

		m_min = 0.0f;
		m_max = 0.0f;
		m_avg = 0.0f;
	}

	void pushSample(float value)
	{
		m_values[m_offset] = value;
		m_offset = (m_offset + 1) % kNumSamples;

		float min = bx::kFloatMax;
		float max = -bx::kFloatMax;
		float avg = 0.0f;

		for (uint32_t ii = 0; ii < kNumSamples; ++ii)
		{
			const float val = m_values[ii];
			min = bx::min(min, val);
			max = bx::max(max, val);
			avg += val;
		}

		m_min = min;
		m_max = max;
		m_avg = avg / kNumSamples;
	}

	int32_t m_offset;
	float m_values[kNumSamples];

	float m_min;
	float m_max;
	float m_avg;
};

static bool bar(float _width, float _maxWidth, float _height, const ImVec4& _color)
{
	const ImGuiStyle& style = ImGui::GetStyle();

	ImVec4 hoveredColor(
		_color.x + _color.x * 0.1f
		, _color.y + _color.y * 0.1f
		, _color.z + _color.z * 0.1f
		, _color.w + _color.w * 0.1f
	);

	ImGui::PushStyleColor(ImGuiCol_Button, _color);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoveredColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, _color);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, style.ItemSpacing.y));

	bool itemHovered = false;

	ImGui::Button("", ImVec2(_width, _height));
	itemHovered |= ImGui::IsItemHovered();

	ImGui::SameLine();
	ImGui::InvisibleButton("", ImVec2(bx::max(1.0f, _maxWidth - _width), _height));
	itemHovered |= ImGui::IsItemHovered();

	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(3);

	return itemHovered;
}

static SampleData s_frameTime;
static bool s_showStats;

static void DrawPerformanceGraphInImgui()
{
	s_showStats ^= ImGui::Button(ICON_FA_BAR_CHART);
	
	const bgfx::Stats* stats = bgfx::getStats();
	const double toMsCpu = 1000.0 / stats->cpuTimerFreq;
	const double toMsGpu = 1000.0 / stats->gpuTimerFreq;
	const double frameMs = double(stats->cpuTimeFrame) * toMsCpu;

	s_frameTime.pushSample(float(frameMs));

	char frameTextOverlay[256];
	bx::snprintf(frameTextOverlay, BX_COUNTOF(frameTextOverlay), "%s%.3fms, %s%.3fms\nAvg: %.3fms, %.1f FPS"
		, ICON_FA_ARROW_DOWN
		, s_frameTime.m_min
		, ICON_FA_ARROW_UP
		, s_frameTime.m_max
		, s_frameTime.m_avg
		, 1000.0f / s_frameTime.m_avg
	);

	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImColor(0.0f, 0.5f, 0.15f, 1.0f).Value);
	ImGui::PlotHistogram("Frame"
		, s_frameTime.m_values
		, SampleData::kNumSamples
		, s_frameTime.m_offset
		, frameTextOverlay
		, 0.0f
		, 60.0f
		, ImVec2(0.0f, 45.0f)
	);
	ImGui::PopStyleColor();

	ImGui::Text("Submit CPU %0.3f, GPU %0.3f (L: %d)"
		, double(stats->cpuTimeEnd - stats->cpuTimeBegin) * toMsCpu
		, double(stats->gpuTimeEnd - stats->gpuTimeBegin) * toMsGpu
		, stats->maxGpuLatency
	);

	if (-INT64_MAX != stats->gpuMemoryUsed)
	{
		char tmp0[64];
		bx::prettify(tmp0, BX_COUNTOF(tmp0), stats->gpuMemoryUsed);

		char tmp1[64];
		bx::prettify(tmp1, BX_COUNTOF(tmp1), stats->gpuMemoryMax);

		ImGui::Text("GPU mem: %s / %s", tmp0, tmp1);
	}
	
	ImGui::Text("Waiting for render thread %0.6f [ms]", double(stats->waitRender) * toMsCpu);
	ImGui::Text("Waiting for submit thread %0.6f [ms]", double(stats->waitSubmit) * toMsCpu);

	if (s_showStats)
	{
		ImGui::SetNextWindowSize(
			ImVec2(300.0f, 500.0f)
			, ImGuiCond_FirstUseEver
		);

		if (ImGui::Begin(ICON_FA_BAR_CHART " Stats", &s_showStats))
		{
			//TODO: I don't care for this at the moment, but it could be useful later on
			/*if (ImGui::CollapsingHeader(ICON_FA_PUZZLE_PIECE " Resources"))
			{
				const bgfx::Caps* caps = bgfx::getCaps();

				const float itemHeight = ImGui::GetTextLineHeightWithSpacing();
				const float maxWidth = 90.0f;

				ImGui::PushFont(ImGui::Font::Mono);
				ImGui::Text("Res: Num  / Max");
				resourceBar("DIB", "Dynamic index buffers", stats->numDynamicIndexBuffers, caps->limits.maxDynamicIndexBuffers, maxWidth, itemHeight);
				resourceBar("DVB", "Dynamic vertex buffers", stats->numDynamicVertexBuffers, caps->limits.maxDynamicVertexBuffers, maxWidth, itemHeight);
				resourceBar(" FB", "Frame buffers", stats->numFrameBuffers, caps->limits.maxFrameBuffers, maxWidth, itemHeight);
				resourceBar(" IB", "Index buffers", stats->numIndexBuffers, caps->limits.maxIndexBuffers, maxWidth, itemHeight);
				resourceBar(" OQ", "Occlusion queries", stats->numOcclusionQueries, caps->limits.maxOcclusionQueries, maxWidth, itemHeight);
				resourceBar("  P", "Programs", stats->numPrograms, caps->limits.maxPrograms, maxWidth, itemHeight);
				resourceBar("  S", "Shaders", stats->numShaders, caps->limits.maxShaders, maxWidth, itemHeight);
				resourceBar("  T", "Textures", stats->numTextures, caps->limits.maxTextures, maxWidth, itemHeight);
				resourceBar("  U", "Uniforms", stats->numUniforms, caps->limits.maxUniforms, maxWidth, itemHeight);
				resourceBar(" VB", "Vertex buffers", stats->numVertexBuffers, caps->limits.maxVertexBuffers, maxWidth, itemHeight);
				resourceBar(" VL", "Vertex layouts", stats->numVertexLayouts, caps->limits.maxVertexLayouts, maxWidth, itemHeight);
				ImGui::PopFont();
			}*/

			if (ImGui::CollapsingHeader(ICON_FA_CLOCK_O " Profiler"))
			{
				if (0 == stats->numViews)
				{
					ImGui::Text("Profiler is not enabled.");
				}
				else
				{
					if (ImGui::BeginChild("##view_profiler", ImVec2(0.0f, 0.0f)))
					{
						ImGui::PushFont(ImGui::Font::Mono);

						ImVec4 cpuColor(0.5f, 1.0f, 0.5f, 1.0f);
						ImVec4 gpuColor(0.5f, 0.5f, 1.0f, 1.0f);

						const float itemHeight = ImGui::GetTextLineHeightWithSpacing();
						const float itemHeightWithSpacing = ImGui::GetFrameHeightWithSpacing();
						const double toCpuMs = 1000.0 / double(stats->cpuTimerFreq);
						const double toGpuMs = 1000.0 / double(stats->gpuTimerFreq);
						const float  scale = 3.0f;

						if (ImGui::ListBoxHeader("Encoders", ImVec2(ImGui::GetWindowWidth(), stats->numEncoders * itemHeightWithSpacing)))
						{
							ImGuiListClipper clipper(stats->numEncoders, itemHeight);

							while (clipper.Step())
							{
								for (int32_t pos = clipper.DisplayStart; pos < clipper.DisplayEnd; ++pos)
								{
									const bgfx::EncoderStats& encoderStats = stats->encoderStats[pos];

									ImGui::Text("%3d", pos);
									ImGui::SameLine(64.0f);

									const float maxWidth = 30.0f * scale;
									const float cpuMs = float((encoderStats.cpuTimeEnd - encoderStats.cpuTimeBegin) * toCpuMs);
									const float cpuWidth = bx::clamp(cpuMs * scale, 1.0f, maxWidth);

									if (bar(cpuWidth, maxWidth, itemHeight, cpuColor))
									{
										ImGui::SetTooltip("Encoder %d, CPU: %f [ms]"
											, pos
											, cpuMs
										);
									}
								}
							}

							ImGui::ListBoxFooter();
						}

						ImGui::Separator();

						if (ImGui::ListBoxHeader("Views", ImVec2(ImGui::GetWindowWidth(), stats->numViews * itemHeightWithSpacing)))
						{
							ImGuiListClipper clipper(stats->numViews, itemHeight);

							while (clipper.Step())
							{
								for (int32_t pos = clipper.DisplayStart; pos < clipper.DisplayEnd; ++pos)
								{
									const bgfx::ViewStats& viewStats = stats->viewStats[pos];

									ImGui::Text("%3d %3d %s", pos, viewStats.view, viewStats.name);

									const float maxWidth = 30.0f * scale;
									const float cpuWidth = bx::clamp(float(viewStats.cpuTimeElapsed * toCpuMs) * scale, 1.0f, maxWidth);
									const float gpuWidth = bx::clamp(float(viewStats.gpuTimeElapsed * toGpuMs) * scale, 1.0f, maxWidth);

									ImGui::SameLine(64.0f);

									if (bar(cpuWidth, maxWidth, itemHeight, cpuColor))
									{
										ImGui::SetTooltip("View %d \"%s\", CPU: %f [ms]"
											, pos
											, viewStats.name
											, viewStats.cpuTimeElapsed * toCpuMs
										);
									}

									ImGui::SameLine();
									if (bar(gpuWidth, maxWidth, itemHeight, gpuColor))
									{
										ImGui::SetTooltip("View: %d \"%s\", GPU: %f [ms]"
											, pos
											, viewStats.name
											, viewStats.gpuTimeElapsed * toGpuMs
										);
									}
								}
							}

							ImGui::ListBoxFooter();
						}

						ImGui::PopFont();
					}

					ImGui::EndChild();
				}
			}
		}
		ImGui::End();
	}
}
#pragma endregion 

void xmain(int _argc, const char** _argv)
{
	std::cerr << "ERROR: This is the entry point of CrossWindow. I am not using CrossWindow at the moment, try to remove CrossWindow in target_link_library!!!!" << std::endl;
}

static std::unique_ptr<gainput::InputManager> inputManager = nullptr;
static std::unique_ptr<gainput::InputMap> inputMap = nullptr;
#if BX_PLATFORM_WINDOWS
static bool ProcessMessage(MSG& msg)
{
	inputManager->HandleMessage(msg);

	return false;
}
#elif (BX_PLATFORM_BSD || BX_PLATFORM_LINUX || BX_PLATFORM_RPI)
static bool ProcessMessage(XEvent& evt)
{
	//inputManager->HandleMessage(evt);

	return false;
}
#endif

int _main_(int _argc, char** _argv)
{
	using namespace eyos;

	std::cout << "Hello CMake & BGFX :)\n" << '\n';
	std::cout << "Running from: " << std::filesystem::current_path() << '\n';

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

	inputManager = std::make_unique<gainput::InputManager>();
	inputManager->SetDisplaySize(width, height);
	auto keyboard = inputManager->CreateAndGetDevice<gainput::InputDeviceKeyboard>();
	auto mouse = inputManager->CreateAndGetDevice<gainput::InputDeviceMouse>();
	inputMap = std::make_unique<gainput::InputMap>( *inputManager );

	entry::SetNativeMessageCallback(&ProcessMessage);

	{
		auto& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	}
	{
		auto& io = ImGui::GetIO();
		io.KeyMap[ImGuiKey_Tab] = gainput::KeyTab;
		io.KeyMap[ImGuiKey_LeftArrow] = gainput::KeyLeft;
		io.KeyMap[ImGuiKey_RightArrow] = gainput::KeyRight;
		io.KeyMap[ImGuiKey_UpArrow] = gainput::KeyUp;
		io.KeyMap[ImGuiKey_DownArrow] = gainput::KeyDown;
		io.KeyMap[ImGuiKey_PageUp] = gainput::KeyPageUp;
		io.KeyMap[ImGuiKey_PageDown] = gainput::KeyPageDown;
		io.KeyMap[ImGuiKey_Home] = gainput::KeyHome;
		io.KeyMap[ImGuiKey_End] = gainput::KeyEnd;
		io.KeyMap[ImGuiKey_Insert] = gainput::KeyInsert;
		io.KeyMap[ImGuiKey_Delete] = gainput::KeyDelete;
		io.KeyMap[ImGuiKey_Backspace] = gainput::KeyBackSpace;
		io.KeyMap[ImGuiKey_Space] = gainput::KeySpace;
		io.KeyMap[ImGuiKey_Enter] = gainput::KeyReturn;
		io.KeyMap[ImGuiKey_Escape] = gainput::KeyEscape;
		io.KeyMap[ImGuiKey_KeyPadEnter] = gainput::KeyKpEnter;
		io.KeyMap[ImGuiKey_A] = gainput::KeyA;
		io.KeyMap[ImGuiKey_C] = gainput::KeyC;
		io.KeyMap[ImGuiKey_V] = gainput::KeyV;
		io.KeyMap[ImGuiKey_X] = gainput::KeyX;
		io.KeyMap[ImGuiKey_Y] = gainput::KeyY;
		io.KeyMap[ImGuiKey_Z] = gainput::KeyZ;
	}
	

	EyosEcs ecs{};

	// Fill ecs for testing
	Mesh* bunnyMesh = meshLoad(/*"meshes/Swordsman2.bin"*/ "meshes/Knight.bin");
	Material testMaterial{};
	{
		EntityId model = ecs.CreateEntity();
		ecs.Assign(model, cmps::Transform{ glm::vec3{0, 0, 0}, glm::quat{ glm::vec3{} } });
		ecs.Assign(model, cmps::Model3D{ bunnyMesh, &testMaterial });
	}
	{
		EntityId model = ecs.CreateEntity();
		ecs.Assign(model, cmps::Transform{ glm::vec3{25, 0, 0}, glm::quat{ glm::vec3{0, 0, 0} }, glm::vec3{ 0.25f } });
		ecs.Assign(model, cmps::Model3D{ bunnyMesh, &testMaterial });
	}

	std::cout << EntityId{ 420, 69 };

	//////////////////
	
	gen::Image image(512, 512);
	double frequency = 2.0;
	int octaves = 2;
	std::uint32_t seed = 2;

	const gen::PerlinNoise perlin(seed);
	const double fx = image.Width() / frequency;
	const double fy = image.Height() / frequency;

	for (int y = 0; y < image.Height(); ++y)
	{
		for (int x = 0; x < image.Width(); ++x)
		{
			const gen::RGBI color(perlin.octaveNoise0_1(x / fx, y / fy, octaves));

			image.Set(x, y, color);
		}
	}

	std::stringstream ss;
	
	ss << 'f' << frequency << 'o' << octaves << '_' << seed << ".bmp";
	std::string path = "../data/maps/";
	path += ss.str();
	if (image.SaveBMP(path.c_str()))
	{
		std::cout << "...saved \"" << ss.str() << "\"\n";
	}
	else
	{
		std::cout << "...failed\n";
	}

	uint32_t size = image.size;
	std::vector<std::uint8_t> data = image.fLine;
	///////////////////

	bimg::ImageContainer* heightmap = imageLoad( path.c_str(), bgfx::TextureFormat::R8);
	RenderableTerrain terrain{ static_cast<char*>(heightmap->m_data), heightmap->m_width, heightmap->m_height };
	terrain.GenerateMesh();


	Camera camera{};
	camera.position = { 0, 12, 35 };
	camera.rotation = glm::quat{ glm::vec3{0.0, 0.0, 0.0} };

	auto debugRenderer = renderer->GetDebugRenderer();
	debugRenderer->AddLine({ 0, 0, 0 }, { 115, 15, 15 }, 10.f, 0xFFFF00FF);

	bool openSpawnWindow = true;
	//For unit spawning tool
	glm::ivec2 amount{ 3, 3 };
	glm::vec2 startPos{ 0, 0 };
	
	while (true)
	{
		inputManager->Update();
		if(keyboard->GetBool(gainput::KeyK)) {
			std::cout << "K is pressed!!\n";
		}
		
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

		{
			auto& io = ImGui::GetIO();

			std::fill_n(io.KeysDown, 512, false);

			
			io.KeyShift = keyboard->GetBool(gainput::KeyShiftL) | keyboard->GetBool(gainput::KeyShiftR);
			io.KeyCtrl = keyboard->GetBool(gainput::KeyCtrlL) | keyboard->GetBool(gainput::KeyCtrlR);
			io.KeyAlt = keyboard->GetBool(gainput::KeyAltL) | keyboard->GetBool(gainput::KeyAltR);
			
			std::array<gainput::DeviceButtonSpec, 16> buttons{};
			auto buttonAmount = keyboard->GetAnyButtonDown(buttons.data(), buttons.size());
			for (size_t i = 0; i < buttonAmount; ++i) {
				std::cout << "Button #" << i << ": " << static_cast<int32_t>(buttons[i].buttonId) << '\n';
				io.KeysDown[buttons[i].buttonId] = true;
			}

			char c = keyboard->GetNextCharacter();
			while(c != 0) {
				io.AddInputCharacter(c);
				
				c = keyboard->GetNextCharacter();
			}
		}
		ImGui::SetNextWindowSize(
			ImVec2(300.0f, 210.0f)
			, ImGuiCond_FirstUseEver
		);
		ImGui::Begin("EyosRenderer ImGUI");
		ImGui::Text("%s", "EyosRenderer Imgui Test");
		DrawPerformanceGraphInImgui();
		ImGui::End();

		camera.DoFreecamMovement(0.5f, 0.01f, mouseState);
		
		if (mouse->GetBool(gainput::MouseButtonLeft)) {
			eyos::Ray ray = camera.ScreenpointToRay(mouseState.m_mx, mouseState.m_my, width, height);
			debugRenderer->AddLine(ray.origin, ray.origin + ray.direction * ray.maxDistance, 8.f, 0xFFFF00FF);
		}
		if (keyboard->GetBool(gainput::KeyG)) {
			glm::vec3 hitPos;
			glm::vec3 normal;
			if (terrain.terrain.GetHeightAt(glm::vec2{ camera.position.x, camera.position.z }, &hitPos, &normal)) {
				debugRenderer->AddLine(hitPos, hitPos + glm::vec3{ 0, 115, 0 }, 14.f, 0xFF0000FF);
				debugRenderer->AddLine(hitPos, hitPos + normal*10.f, 14.f, 0x00FF00FF);
			}
		}

		ImGui::SetNextWindowPos(
			ImVec2(350.0f, 50.0f)
			, ImGuiCond_FirstUseEver
		);
		if(ImGui::Begin("Unit Spawn Menu", &openSpawnWindow)) {
			ImGui::Text("Spawn knights:");

			ImGui::InputFloat2("Start position", glm::value_ptr(startPos));
			ImGui::InputInt2("Amount", glm::value_ptr(amount));
			if(ImGui::Button("Spawn units")) {
				std::cout << "Spawning " << amount.x * amount.y << " Units\n";
			}
		}
		ImGui::End();

		
		renderer->BeginRender(camera);
		renderer->RenderWorld(ecs, camera);
		terrain.generatedMesh->submit(0, renderer->GetMeshShaderProgram(), glm::value_ptr(glm::mat4{ 1.0f }), BGFX_STATE_DEFAULT | BGFX_STATE_PT_TRISTRIP);
		renderer->EndRender();
		imguiEndFrame();
	}

	if (!renderer->Shutdown()) {
		std::cerr << "Failed to shutdown!" << std::endl;
		return 2;
	}

	return 0;
}
