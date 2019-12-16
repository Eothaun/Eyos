#pragma once
#include <glm/glm.hpp>
#include <bgfx/bgfx.h>

namespace eyos {
	struct Material {
		Material() = default;

		glm::vec4 color{ 1.f, 1.f, 1.f, 1.f };
		bgfx::TextureHandle texture{bgfx::kInvalidHandle};
	};
}
