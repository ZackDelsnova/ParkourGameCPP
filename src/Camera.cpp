#include "Camera.h"

// conmstructor
Camera::Camera(glm::vec3 startPos) {
	Position = startPos;
	WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Yaw = -90.0f; // facing towards negative z by default
	Pitch = 0.0f;
	Speed = 3.0f;
	Sensitivity = 0.1f;
	updateCameraVectors();
}

// return view matrix
glm::mat4 Camera::GetViewMatrix() const {
	return glm::lookAt(Position, Position + Front, Up);
}

// keyboard input processing
void Camera::HandleKeyboardMovement(const bool* keys, float deltaTime) {
	float velocity = Speed * deltaTime;
	if (keys[SDL_SCANCODE_W]) Position += Front * velocity;
	if (keys[SDL_SCANCODE_S]) Position -= Front * velocity;
	if (keys[SDL_SCANCODE_A]) Position -= Right * velocity;
	if (keys[SDL_SCANCODE_D]) Position += Right * velocity;
}

// mouse movement processing
void Camera::HandleMouseLook(float xoffset, float yoffset) {
	xoffset *= Sensitivity;
	yoffset *= Sensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// constrain pitch
	if (Pitch > 89.0f) Pitch = 89.0f;
	if (Pitch < -89.0f) Pitch = -89.0f;

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
