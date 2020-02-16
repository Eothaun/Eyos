#pragma once
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
		void Update();
		void Shutdown();
	private:
		World<EyosEcs> world {};
		Renderer renderer {};
		entry::WindowHandle windowHandle {0};
		Input input {};
	public:
		std::uint32_t width { 1280 };
		std::uint32_t height { 720 };
	};
}