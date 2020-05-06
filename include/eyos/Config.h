#pragma once
namespace eyos::setting {

	constexpr  const char eyos_version[]{ "0.1" };

	namespace terrain{
		constexpr float frequency{ 2.0f };
		constexpr int imageSize{ 512 };
		constexpr int octaves{ 2 };
		constexpr int seed{ 2 };
		constexpr const  char path[128]{ "../data/maps/" };
	}

	namespace window {
		constexpr unsigned int width{ 1280 };
		constexpr unsigned int height{ 720 };
	}

	namespace time {
		constexpr double maxTimeStep{ 0.0333 };
		constexpr double maxSteps{ 6};

	}

	namespace camera {
		constexpr float fov{ 45.f };
		constexpr float nearZ { 0.5f};
		constexpr float farZ{ 500.f };
	}
}