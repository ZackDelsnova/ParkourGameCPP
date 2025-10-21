#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL3/SDL.h>

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
	float Speed; // movement speed
	float Sensitivity; // mouse sensitivity

	Camera(glm::vec3 startPos);

	glm::mat4 GetViewMatrix() const;
	void HandleKeyboardMovement(const bool* keys, float deltaTime);
	void HandleMouseLook(float xoffset, float yoffset);

private:
	void updateCameraVectors();
};