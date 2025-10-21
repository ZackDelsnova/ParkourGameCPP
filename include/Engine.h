#pragma once
#include <SDL3/SDL.h>
#include "Renderer.h"
#include "Camera.h"
#include "DebugOverlay.h"

class Engine {
public:
	Engine(int w, int h);

	Renderer renderer;
	Camera camera;
	DebugOverlay debug;

	bool Init();
	void Run();
	void Shutdown();

private:
	int windowWidth, windowHeight;

	SDL_Window* window = nullptr;
	SDL_GLContext glContext = nullptr;
	bool isRunning = false;
	bool mouseLocked = false;

	void ProcessInput(float deltaTime);
};
