#pragma once
#include <glm/glm.hpp>
#include <glm/ext/quaternion_float.hpp>
#include "entry/input.h"
#include "engine/geometry/Ray.h"


namespace eyos {
	//! A Camera with FreeCam movement support
	class Camera {
	public:
		Camera() = default;

		glm::vec3 position{ 0, 0, 0 };
		glm::quat rotation{};
		glm::vec3 relativeRotation{};

		// fovy
		float fov = 45.f;
		float nearZ = 0.5f;
		float farZ = 500.f;

		//HARDCODED MOVE TO IMGUI WINDOW
		glm::vec2 XRange{ 0,500 };
		glm::vec2 YRange{ 0,500 };
		glm::vec2 ZRange{ 300,500 };
		glm::vec3 startPosPlayCam{ 200,400,200 };
		glm::vec3 startRotPlayCam{ glm::radians(-90.f),0,0 };
		bool freeMovement = true;

	private:
		bool wasRMBDown = false;
		glm::vec2 lastMousePos{-1, -1};
		glm::vec2 freeCamEuler{0, 0};

	public:
		void ToggleFreeCameraMovement(bool toggle);
		void DoMovement(float movementSpeed, float rotationSpeed, const entry::MouseState& mouseState);

		void DoPlayCamMovement(float movementSpeed, float rotationSpeed, const entry::MouseState& mouseState);
		void DoFreecamMovement(float movementSpeed, float rotationSpeed, const entry::MouseState& mouseState);
		
		Ray ScreenpointToRay(uint32_t screenX, uint32_t screenY, uint32_t screenWidth, uint32_t screenHeight);

		glm::mat4 GetModelMatrix() const;
		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix(float aspectRatio) const;
	};
}