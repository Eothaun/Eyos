#pragma once
#include <glm/glm.hpp>
#include <glm/ext/quaternion_float.hpp>

namespace eyos 
{
	namespace rendering_components {
		struct Transform {
			Transform() = default;
			Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale = glm::vec3{ 1.f, 1.f, 1.f })
				: position(position), rotation(rotation), scale(scale) {}

			glm::vec3 position;
			glm::quat rotation;
			glm::vec3 scale;
		};

		//TODO: Move the generic components over to Engine
		struct GridPosition {
			glm::ivec2 position;
		};

		struct Model3D {
			int mesh;
			int material;
		};

		struct InstancedModel {
			int mesh;
			int material;
			int instancedBucket;
		};
	}
}