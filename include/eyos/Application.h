#pragma once
#include "eyos/Config.h"
#include "engine/World.h"
#include "eyos/ClientEcsType.h"
#include "eyos/GameEvents.h"
#include "eyos/rendering/EyosRenderer.h"
#include "eyos/Input.h"


namespace eyos {
	class Application {
	public:
	public:
		void Init(int _argc, char** _argv);
		void Gameloop();
		void Shutdown();
	private:
		World<EyosEcs> world {};
		Renderer renderer {};
		entry::WindowHandle windowHandle {0};
		Input input {};
	public:
		std::uint32_t width { setting::window::width };
		std::uint32_t height { setting::window::height };
	};
}