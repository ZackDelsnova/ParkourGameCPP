#include "DebugOverlay.h"

void DebugOverlay::Update(float deltaTime, const Camera& camera) {
	fpsTimer += deltaTime;
	frameCount++;
	if (fpsTimer >= 1.0f) {
		std::cout << "FPS: " << frameCount << " | "
				  << "Camera Position: (" << camera.Position.x << ", "
				  << camera.Position.y << ", " << camera.Position.z << ")\n";
		fpsTimer = 0.0f;
		frameCount = 0;
	}
}
