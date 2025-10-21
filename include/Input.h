#pragma once
#include <SDL3/SDL.h>
#include <glm/glm.hpp>

class Input {
public:
	void CaptureInput();
	bool IsKeyPressed(SDL_Scancode key) const;
	glm::vec2 GetMouseDelta() const;
	bool ShouldQuit() const;
	void LockMouse(bool locked);

private:
	const bool* keyStates = SDL_GetKeyboardState(nullptr);
	glm::vec2 lastMousePos = { 0.0f, 0.0f };
	glm::vec2 mouseDelta = { 0.0f, 0.0f };
	bool quitRequested = false;
	bool mouseLocked = false;
};
