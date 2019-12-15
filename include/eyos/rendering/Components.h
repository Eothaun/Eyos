#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "bgfx_utils.h"

#include "eyos/rendering/Material.h"


namespace eyos 
{
	namespace rendering_components {
		//TODO: Move the generic components over to Engine
		struct Transform {
			Transform() = default;
			Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale = glm::vec3{ 1.f, 1.f, 1.f })
				: position(position), rotation(rotation), scale(scale) {}

			glm::vec3 position;
			glm::quat rotation;
			glm::vec3 scale;

			glm::mat4 GetModelMatrix() const {
				glm::mat4 modelMat{ 1.0f };

				modelMat = glm::translate(modelMat, position);
				modelMat = modelMat * glm::toMat4(rotation);
				modelMat = glm::scale(modelMat, scale);

				return modelMat;
			}
		};

		//TODO: Move the generic components over to Engine
		struct GridPosition {
			glm::ivec2 position;
		};

		struct Model3D {
			Mesh* mesh;
			Material* material;
		};

		struct InstancedModel {
			Mesh* mesh;
			Material* material;
			int instancedBucket;
		};
	}
}