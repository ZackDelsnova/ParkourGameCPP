#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include "Camera.h"
#include "Renderer.h"

int main(int argc, char* argv[])
{
    // sdl + opengl setup
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL failed to init: " << SDL_GetError() << std::endl;
        return -1;
    }

	int windowWidth = 1280, windowHeight = 720;

    SDL_Window* window = SDL_CreateWindow("fps parkour test",
        windowWidth, windowHeight, SDL_WINDOW_OPENGL);

    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
		SDL_Quit();
        return -1;
    }

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
        return -1;
	}

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
		SDL_GL_DestroyContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	Renderer renderer;
	renderer.Init(windowWidth, windowHeight);

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	// mouse stuff
	float lastX = windowWidth / 2.0f;
	float lastY = windowHeight / 2.0f;
	bool firstMouse = true;
	SDL_CaptureMouse(true);
	SDL_HideCursor(); // optional: hide cursor

	bool running = true;
	SDL_Event event;
	float deltaTime = 0.0f;
	uint64_t lastTicks = SDL_GetTicks();
	int frameCount = 0;
	float fpsTimer = 0.0f;

    while (running) {
		uint64_t currentTicks = SDL_GetTicks();
		deltaTime = (currentTicks - lastTicks) / 1000.0f;
        lastTicks = currentTicks;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
            if (event.type == SDL_EVENT_MOUSE_MOTION)
				camera.ProcessMouse((float)event.motion.xrel, -(float)event.motion.yrel);
        }

		// keyboard
		const bool* keys = SDL_GetKeyboardState(NULL);
		camera.ProcessKeyboard(keys, deltaTime);

		// mouse
		float mx, my;
		Uint32 mouseState = SDL_GetMouseState(&mx, &my);
		if (mx >= 0 && mx < windowWidth && my >= 0 && my < windowHeight) {
			if (firstMouse) {
				lastX = mx;
				lastY = my;
				firstMouse = false;
			}

			float xoffset = mx - lastX;
			float yoffset = lastY - my; // reversed since y-coordinates go from bottom to top
			lastX = mx;
			lastY = my;
			camera.ProcessMouse(xoffset, yoffset);
		}

		// debug overlay fps
		frameCount++;
		fpsTimer += deltaTime;
		if (fpsTimer >= 1.0f) {
			std::cout << "FPS: " << frameCount
				<< " | Pos: (" << camera.Position.x << ","
				<< camera.Position.y << "," << camera.Position.z << ")\n";
			frameCount = 0;
			fpsTimer = 0.0f;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.Draw(camera);
		SDL_GL_SwapWindow(window);

    }

	renderer.Cleanup();
	SDL_GL_DestroyContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
    return 0;
}
