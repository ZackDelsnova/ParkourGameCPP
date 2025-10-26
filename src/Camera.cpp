#include "Camera.h"

// conmstructor
Camera::Camera(glm::vec3 startPos) {
	Position = startPos;
	WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Yaw = -90.0f; // facing towards negative z by default
	Pitch = 0.0f;
	Sensitivity = 0.1f;
	updateCameraVectors();
}

// return view matrix
glm::mat4 Camera::GetViewMatrix() const {
	return glm::lookAt(Position, Position + Front, Up);
}

// mouse movement processing
void Camera::HandleMouseLook(float xoffset, float yoffset) {
	xoffset *= Sensitivity;
	yoffset *= Sensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// constrain pitch
	if (Pitch < minPitch + softZone) {
		float t = (Pitch - (minPitch + softZone)) / -softZone;
		float softness = 1.0f - glm::smoothstep(0.0f, 1.0f, t);
		Pitch = minPitch + softZone * softness;
	}

	if (Pitch > maxPitch) Pitch = maxPitch;

	updateCameraVectors();
}

// update camera vectors based on yaw and pitch
void Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}
