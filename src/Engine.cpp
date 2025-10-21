#include "Engine.h"
#include <iostream>

Engine::Engine(int w, int h) : player(glm::vec3(0.0f, 1.5f, 0.0f)){
	windowWidth = w;
	windowHeight = h;
}

bool Engine::Init() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "SDL failed to init: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow("fps parkour test",
		windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	
	if (!window) {
		std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	glContext = SDL_GL_CreateContext(window);
	if (!glContext) {
		std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cerr << "Failed to initialize GLAD!" << std::endl;
		SDL_GL_DestroyContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	
	renderer.Init(windowWidth, windowHeight);
	isRunning = true;
	return true;
}

void Engine::Run() {
	Uint64 lastTicks = SDL_GetTicks();
	while (isRunning) {
		Uint64 currentTicks = SDL_GetTicks();
		float deltaTime = (currentTicks - lastTicks) / 1000.0f;
		lastTicks = currentTicks;

		ProcessInput(deltaTime);
		renderer.RenderScene(player.camera);
		debug.Update(deltaTime, player);

		SDL_GL_SwapWindow(window);
	}
}

void Engine::ProcessInput(float deltaTime) {
	SDL_Event e;
	const bool* keys = SDL_GetKeyboardState(nullptr);

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) isRunning = false;

		if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
			// press ESC to release mouse
			SDL_SetWindowRelativeMouseMode(window, false);
			SDL_CaptureMouse(false);
			mouseLocked = false;
		}

		if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN && e.button.button == SDL_BUTTON_LEFT) {
			// click to capture mouse
			if (!mouseLocked) {
				SDL_SetWindowRelativeMouseMode(window, true);
				SDL_CaptureMouse(true);
				mouseLocked = true;
			}
		}
	}

	player.Update(deltaTime, keys, renderer.objects);

	if (mouseLocked) {
		float mx, my;
		SDL_GetRelativeMouseState(&mx, &my);
		player.camera.HandleMouseLook(mx, -my);
	}
}

void Engine::Shutdown() {
	renderer.Shutdown();
	SDL_GL_DestroyContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
