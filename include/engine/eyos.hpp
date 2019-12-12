#pragma once
#undef BUILD_SHARED_LIBS
#include <engine/Defines.hpp>
namespace eyos {
EYOS_API int calculate_value();
EYOS_API float calculate_float();
EYOS_API double calculate_double();
EYOS_API unsigned long long calculate_unit64();
} // namespace eyos
