#include "eyos/Input.h"
#include <imgui/imgui.h>

void eyos::Input::Init(std::uint32_t width, std::uint32_t height) {
	inputManager.SetDisplaySize(width, height);
	keyboard = inputManager.CreateAndGetDevice<gainput::InputDeviceKeyboard>();
	mouse = inputManager.CreateAndGetDevice<gainput::InputDeviceMouse>();
	// SETUP IMGUI
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
}