#pragma once
#include <type_traits>


namespace eyos
{
	namespace ecs_builtins {
		struct EcsTrackable {};

		static_assert(std::is_empty_v<EcsTrackable>, "The ecs depends on this being a 0 size struct");
	}
}
