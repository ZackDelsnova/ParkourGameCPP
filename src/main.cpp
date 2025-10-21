#include "Engine.h"

int main() {
	Engine engine;
	if (!engine.Init(1280, 720)) {
		return -1;
	}

	engine.Run();
	engine.Shutdown();
	return 0;
}
