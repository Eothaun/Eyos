#pragma once
#include <glm/glm.hpp>
#include <glm/ext/quaternion_float.hpp>
#include "entry/input.h"


namespace eyos {
	//! A Camera with FreeCam movement support
	class Camera {
	public:
		Camera() = default;

		glm::vec3 position{ 0, 0, 0 };
		glm::quat rotation{};

		// fovy
		float fov = 45.f;
		float nearZ = 0.5f;
		float farZ = 500.f;

	private:
		bool wasRMBDown = false;
		glm::vec2 lastMousePos{-1, -1};
		glm::vec2 freeCamEuler{0, 0};

	public:
		void DoFreecamMovement(float movementSpeed, float rotationSpeed, const entry::MouseState& mouseState);

		glm::mat4 GetModelMatrix() const;
		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix(float aspectRatio) const;
	};
}