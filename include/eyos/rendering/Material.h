#include <glm/glm.hpp>
#include <bgfx/bgfx.h>

namespace eyos {
	struct Material {
		glm::vec4 color;
		bgfx::TextureHandle texture;
	};
}
