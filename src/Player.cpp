#include "Player.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <cmath>

Player::Player(const glm::vec3& startPos) :
	camera(startPos),
	position(startPos), 
	velocity(0.0f), 
	onGround(false),
	speed(5.0f), 
	jumpStrength(5.0f), 
	gravity(-9.81f),
	height(1.8f),
	radius(0.3f)
{
	cameraOffset = glm::vec3(0.0f, height * 0.8f, 0.0f);
}

void Player::InitGraphics() {
	auto capsuleMesh = MeshFactory::CreateCapsule(32, 32, radius, height);
	capsule = std::make_shared<Object>(capsuleMesh, position, glm::vec3(0, 1, 1));
}

void Player::Update(float deltaTime, const bool* keys, const std::vector<std::shared_ptr<Object>>& worldObjects) {
	float coyoteTime = 0.1f;
	static bool spacePressedLastFrame = false;

	glm::vec3 move(0.0f);
	if (keys[SDL_SCANCODE_W]) move += camera.Front;
	if (keys[SDL_SCANCODE_S]) move -= camera.Front;
	if (keys[SDL_SCANCODE_A]) move -= camera.Right;
	if (keys[SDL_SCANCODE_D]) move += camera.Right;

	// sprint
	isSprinting = keys[SDL_SCANCODE_LSHIFT];
	float currentSpeed = speed * (isSprinting ? sprintMultiplier : 1.0f);

	move.y = 0.0f; // prevent flying
	if (glm::length(move) > 0.0f) {
		move = glm::normalize(move);
		Move(move, deltaTime * currentSpeed);
	}

	// update coyote timer & jump
	if (onGround) {
		jumpsLeft = maxJumps;
		timeSinceGrounded = 0.0f;
	} else {
		timeSinceGrounded += deltaTime;
	}

	// jump
	bool spacePressed = keys[SDL_SCANCODE_SPACE];
	if (spacePressed && !spacePressedLastFrame) {
		if (jumpsLeft > 0 || timeSinceGrounded < coyoteTime) {
			Jump();
			headBobJumpTimer = 0.1f;
		}
	}
	spacePressedLastFrame = spacePressed;

	// gravity
	if (!onGround) {
		velocity.y += gravity * deltaTime;
	}

	// vertical velocity
	position += velocity * deltaTime;

	// check ground collision
	bool wasGrounded = onGround;
	onGround = CheckGroundCollision(worldObjects);

	// vert vel to 0 when landing
	if (onGround && velocity.y < 0.0f) {
		velocity.y = 0.0f;
		// land camera bob
		if (!wasGrounded) headBobLandTimer = 0.1f;
	}

	capsule->position = position;

	// headbob
	glm::vec3 bobOffset(0.0f);
	if (glm::length(move) > 0.01f) {
		float bobSpeed = headBobFrequency * (isSprinting ? sprintMultiplier : 1.0f);
		headBobTimer += deltaTime * bobSpeed;
		bobOffset.y = std::sin(headBobTimer) * headBobAmplitude;
		bobOffset.x = std::sin(headBobTimer * 0.5f) * headBobAmplitude * 0.5f;
	}
	else {
		headBobTimer = 0.0f;
	}

	if (headBobJumpTimer > 0.0f) {
		bobOffset.y += std::sin((headBobJumpTimer / 0.1f) * glm::pi<float>()) * headBobAmplitude * 0.5f;
		headBobJumpTimer -= deltaTime;
	}

	if (headBobLandTimer > 0.0f) {
		bobOffset.y -= std::sin((headBobLandTimer / 0.1f) * glm::pi<float>()) * headBobAmplitude * 0.5f;
		headBobTimer -= deltaTime;
	}

	camera.Position = position + cameraOffset + bobOffset;

	capsule->rotation.y = camera.Yaw;
}

void Player::Move(const glm::vec3 dir, float deltaTime) {
	position += dir * deltaTime;
}

void Player::Jump() {
	velocity.y = jumpStrength;
	onGround = false;
	jumpsLeft--;
}

void Player::SetPosition(const glm::vec3& pos) {
	position = pos;
	camera.Position = pos;
}

void Player::HandleMouse(float xoffset, float yoffset) {
	camera.HandleMouseLook(xoffset, yoffset);
}

bool Player::CheckGroundCollision(const std::vector<std::shared_ptr<Object>>& worldObjects) {
	float feetY = position.y - height * 0.5f; // bottom of the player capsule
	bool grounded = false;
	float highestY = -FLT_MAX;

	for (const auto& obj : worldObjects) {
		glm::vec3 halfExtents = obj->scale * 0.5f;
		glm::vec3 objMin = obj->position - halfExtents;
		glm::vec3 objMax = obj->position + halfExtents;

		// closest point on AABB to player XZ
		float cloestX = glm::clamp(position.x, objMin.x, objMax.x);
		float cloestZ = glm::clamp(position.z, objMin.z, objMax.z);

		// distance from player to closest point
		float distX = position.x - cloestX;
		float distZ = position.z - cloestZ;
		float distSq = distX * distX + distZ * distZ;
		
		if (distSq <= radius * radius) {
			// chechk vertical overlap
			float topY = objMax.y;
			if (feetY >= topY - 0.05f && feetY <= topY + 0.5f) {
				grounded = true;
				if (topY > highestY) {
					highestY = topY;
				}
			}
		}
	}
	if (grounded) {
		// only snap if falling
		if (velocity.y <= 0.0f) {
			float delta = (highestY + height * 0.5f) - position.y;
			// smooth snap: move fractionally if delta is large
			if (delta > 0.05f) {
				position.y += delta * 0.5f; // adjust for smoothing
			}
			else {
				position.y = highestY + height * 0.5f;
				velocity.y = 0.0f;
			}
			onGround = true;
		}
	} else {
		onGround = false;
	}

	return grounded;
}
