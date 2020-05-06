#include "eyos/Application.h"
#include "eyos/Config.h";
#include <filesystem>
//!!!!!!!!!!!!
//!!! NOTE !!!	THESE INCLUDES ARE AT THE BOTTOM BECAUSE OF MACRO REASONS, DON"T ADD #include s BELOW HERE!!!
//!!!!!!!!!!!!
#if ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_WINDOWS
#include <windows.h>
#elif ENTRY_CONFIG_USE_NATIVE && (BX_PLATFORM_BSD || BX_PLATFORM_LINUX || BX_PLATFORM_RPI)
#include <X11/Xlib.h> // will include X11 which #defines None... Don't mess with order of includes.
#endif

int _main_(int _argc, char** _argv)
{
	std::cout << "Eyos Version: " << eyos::setting::eyos_version << '\n';
	std::cout << "Running from: " << std::filesystem::current_path() << '\n';
	eyos::Application app{};
	app.Init(_argc, _argv);
	app.Gameloop();
	app.Shutdown();
	return 0;
}