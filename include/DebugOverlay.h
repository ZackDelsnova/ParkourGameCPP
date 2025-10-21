#pragma once
#include "Player.h"
#include <iostream>

class DebugOverlay {
public:
	void Update(float deltaTime, Player player);

private:
	float fpsTimer = 0.0f;
	int frameCount = 0;
};
