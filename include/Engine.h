#pragma once
#include <SDL3/SDL.h>
#include "Renderer.h"
#include "Camera.h"
#include "DebugOverlay.h"

class Engine {
public:
	Engine();

	bool Init(int w, int h);
	void Run();
	void Shutdown();

private:
	int windowWidth, windowHeight;

	SDL_Window* window = nullptr;
	SDL_GLContext glContext = nullptr;
	bool isRunning = false;
	bool mouseLocked = false;

	Renderer renderer;
	Camera camera;
	DebugOverlay debug;

	void ProcessInput(float deltaTime);
};
