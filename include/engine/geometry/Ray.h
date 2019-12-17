#pragma once
#include <glm/glm.hpp>

namespace eyos {
	struct Ray {
		glm::vec3 origin;
		glm::vec3 direction;
		float maxDistance;
	};
}