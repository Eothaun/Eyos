#include "engine/World.hpp"

#include "eyos/ClientEcsType.h"
#include "eyos/GameEvents.hpp"
#include "eyos/rendering/EyosRenderer.h"
#include "eyos/Input.hpp"


namespace eyos {
	class Application {
	public:
	public:
		void Init(int _argc, char** _argv);
		void Update();
		void Shutdown();
	private:
		World<EyosEcs, GameEvents> world {};
		Renderer renderer {};
		entry::WindowHandle windowHandle {0};
		Input input {};
	public:
		std::uint32_t width { 1280 };
		std::uint32_t height { 720 };
	};
}