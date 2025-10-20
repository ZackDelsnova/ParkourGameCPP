#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// first person camera class
class Camera {
public:
	glm::vec3 Position; // camera position in world space
	glm::vec3 Front;    // camera front vector
	glm::vec3 Up;       // camera up vector
	glm::vec3 Right;    // camera right vector
	glm::vec3 WorldUp;  // world up vector, usually (0, 1, 0)

	float Yaw;   // yaw angle (in degrees), rotation around y axis
	float Pitch; // pitch angle (in degrees), rotation around x axis
	float MovementSpeed; // movement speed
	float MouseSensitivity; // mouse sensitivity

	Camera(glm::vec3 startPos = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(5.0f), MouseSensitivity(0.1f)
	{
		Position = startPos;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	// keyboard movement
	void ProcessKeyboard(const bool* keys, float deltaTime) {
		float velocity = MovementSpeed * deltaTime;
		if (keys[SDL_SCANCODE_W]) Position += Front * velocity;
		if (keys[SDL_SCANCODE_S]) Position -= Front * velocity;
		if (keys[SDL_SCANCODE_A]) Position -= Right * velocity;
		if (keys[SDL_SCANCODE_D]) Position += Right * velocity;
	}

	// mouse movement
	void ProcessMouseMovement(float xoffset, float yoffset) {
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// constrain pitch
		if (Pitch > 89.0f) Pitch = 89.0f;
		if (Pitch < -89.0f) Pitch = -89.0f;

		updateCameraVectors();
	}

private:
	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};