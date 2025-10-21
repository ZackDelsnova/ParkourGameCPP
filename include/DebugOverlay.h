#pragma once
#include "Camera.h"
#include <iostream>

class DebugOverlay {
public:
	void Update(float deltaTime, const Camera& camera);

private:
	float fpsTimer = 0.0f;
	int frameCount = 0;
};
