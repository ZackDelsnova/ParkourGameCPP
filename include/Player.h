#pragma once
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "Camera.h"
#include "Object.h"
#include "MeshFactory.h"


class Player {
public:
	Camera camera;

	glm::vec3 position;
	glm::vec3 velocity = glm::vec3(0.0f);

	float speed = 5.0f;
	float sprintMultiplier = 1.5f;
	bool isSprinting = false;
	
	float height = 1.8f;
	float radius = 0.3f;
	
	int maxJumps = 2;
	int jumpsLeft = 2;
	bool onGround = false;
	float jumpStrength = 5.0f;
	float gravity = -9.81f;

	float timeSinceGrounded = 0.0f;
	std::shared_ptr<Object> capsule;

	glm::vec3 cameraOffset;
	float headBobTimer = 0.0f;
	float headBobLandTimer = 0.0f;
	float headBobJumpTimer = 0.0f;
	float headBobAmplitude = 0.05f;
	float headBobFrequency = 8.0f;

	Player(const glm::vec3& startPos);

	void Update(float deltaTime, const bool* keys, const std::vector<std::shared_ptr<Object>>& worldObjects);
	void Move(const glm::vec3 dir, float deltaTime);
	void HandleMouse(float xoffset, float yoffset);
	void SetPosition(const glm::vec3& pos);
	void Jump();
	void InitGraphics();
private:
	bool CheckGroundCollision(const std::vector<std::shared_ptr<Object>>& worldObjects);
};
