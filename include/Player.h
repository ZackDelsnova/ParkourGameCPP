#pragma once
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "Camera.h"
#include "Object.h"


class Player {
public:
	Camera camera;
	glm::vec3 position;
	glm::vec3 velocity;

	bool onGround;
	float speed;
	float jumpStrength;
	float gravity;
	float height;
	float radius;
	int maxJumps = 2;
	int jumpsLeft = 2;
	float timeSinceGrounded = 0.0f;

	Player(const glm::vec3& startPos);

	void Update(float deltaTime, const bool* keys, const std::vector<std::shared_ptr<Object>>& worldObjects);
	void Move(const glm::vec3 dir, float deltaTime);
	void HandleMouse(float xoffset, float yoffset);
	void SetPosition(const glm::vec3& pos);
	void Jump();
private:
	bool CheckGroundCollision(const std::vector<std::shared_ptr<Object>>& worldObjects);
};
