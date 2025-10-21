#include "DebugOverlay.h"

void DebugOverlay::Update(float deltaTime, Player player) {
	fpsTimer += deltaTime;
	frameCount++;
	if (fpsTimer >= 1.0f) {
		std::cout << "FPS: " << frameCount << " | "
			<< "Player Position: (" << player.position.x << ", "
			<< player.position.y << ", " << player.position.z << ")\n";
		fpsTimer = 0.0f;
		frameCount = 0;
	}
}
