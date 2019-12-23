#include "eyos/rendering/Camera.h"
#include <glm/gtx/quaternion.hpp>
#include "bgfx_utils.h"
#include "entry/input.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>


namespace eyos {
	void Camera::DoFreecamMovement(float movementSpeed, float rotationSpeed, const entry::MouseState& mouseState)
	{
		glm::vec3 relativeDirection{};

		if (inputGetKeyState(entry::Key::KeyA)) {
			relativeDirection.x -= 1;
		}
		if (inputGetKeyState(entry::Key::KeyD)) {
			relativeDirection.x += 1;
		}
		if (inputGetKeyState(entry::Key::KeyW)) {
			relativeDirection.z -= 1;
		}
		if (inputGetKeyState(entry::Key::KeyS)) {
			relativeDirection.z += 1;
		}
		if (inputGetKeyState(entry::Key::KeyQ)) {
			relativeDirection.y -= 1;
		}
		if (inputGetKeyState(entry::Key::KeyE)) {
			relativeDirection.y += 1;
		}
		if (!glm::epsilonEqual(glm::length2(relativeDirection), 0.0f, 0.01f)) {
			relativeDirection = glm::normalize(relativeDirection);
		}

		glm::vec2 mousePos{ mouseState.m_mx, mouseState.m_my };
		bool isRMBDown = mouseState.m_buttons[3];
		if (!wasRMBDown && isRMBDown) {
			lastMousePos = mousePos;
		}
		if (isRMBDown) {

			freeCamEuler += (lastMousePos - mousePos) * rotationSpeed;

			rotation = glm::quat{ glm::vec3{freeCamEuler.y, freeCamEuler.x, 0.f} };
		}
		lastMousePos = mousePos;
		wasRMBDown = isRMBDown;


		glm::mat4 modelMat = GetModelMatrix();

		glm::vec3 absoluteDirection = glm::vec3{ modelMat * glm::vec4{ relativeDirection, 0 } };
		
		position += absoluteDirection * movementSpeed;
	}

	Ray Camera::ScreenpointToRay(uint32_t screenX, uint32_t screenY, uint32_t screenWidth, uint32_t screenHeight) {
		float aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

		screenY = screenHeight - screenY;

		//project to zfar plane;
		const float zPos = 1.0f;

		glm::vec3 outPoint;
		bool isNegativeToOne = bgfx::getCaps()->homogeneousDepth;
		if (isNegativeToOne) {
			outPoint = glm::unProjectNO(glm::vec3{ screenX, screenY, zPos}, GetViewMatrix(), GetProjectionMatrix(aspectRatio), glm::vec4{ 0, 0, screenWidth, screenHeight });
		} else {
			outPoint = glm::unProjectZO(glm::vec3{ screenX, screenY, zPos }, GetViewMatrix(), GetProjectionMatrix(aspectRatio), glm::vec4{ 0, 0, screenWidth, screenHeight });
		}

		glm::vec3 direction = outPoint - position;
		float length = glm::length(direction);
		direction /= length;
		return Ray{ position, direction, length };
	}

	glm::mat4 Camera::GetModelMatrix() const
	{
		glm::mat4 modelMat{ 1.0f };

		modelMat = glm::translate(modelMat, position);
		modelMat = modelMat * glm::toMat4(rotation);

		return modelMat;
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::inverse(GetModelMatrix());
	}

	glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) const
	{
		bool isNegativeToOne = bgfx::getCaps()->homogeneousDepth;
		if (isNegativeToOne) {
			return glm::perspectiveNO(fov, aspectRatio, nearZ, farZ);
		}
		else
		{
			return glm::perspectiveZO(fov, aspectRatio, nearZ, farZ);
		}
	}
}