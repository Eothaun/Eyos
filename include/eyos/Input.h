#include <gainput/gainput.h>
#include <cstdint>
namespace eyos {
	struct Input {
		gainput::InputManager inputManager{};
		gainput::InputDeviceKeyboard* keyboard{ nullptr };
		gainput::InputDeviceMouse* mouse{ nullptr };
		void Init(std::uint32_t width, std::uint32_t height);
	};
}