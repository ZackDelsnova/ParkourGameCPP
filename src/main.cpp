#include "Engine.h"
#include "Mesh.h"
#include "Object.h"
#include <vector>
#include <memory>

int main() {
	Engine engine(1280, 720);
	if (!engine.Init()) {
		return -1;
	}

    // cube vertices 
    std::vector<float> cubeVerts = {
        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f, 0.5f,-0.5f,
         0.5f, 0.5f,-0.5f, -0.5f, 0.5f,-0.5f, -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f, 0.5f,  0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,-0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,-0.5f, -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f, -0.5f,-0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f,  0.5f, 0.5f,-0.5f,  0.5f,-0.5f,-0.5f,
         0.5f,-0.5f,-0.5f,  0.5f,-0.5f, 0.5f,  0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f,-0.5f, 0.5f,
         0.5f,-0.5f, 0.5f, -0.5f,-0.5f, 0.5f, -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,  0.5f, 0.5f,-0.5f,  0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,-0.5f
    };

	auto cubeMesh = std::make_shared<Mesh>(cubeVerts);

	engine.renderer.AddObject(std::make_shared<Object>(cubeMesh, glm::vec3(0, 0, -3), glm::vec3(1, 0, 0)));
    engine.renderer.AddObject(std::make_shared<Object>(cubeMesh, glm::vec3(2, 0, -3), glm::vec3(0, 1, 0)));
    engine.renderer.AddObject(std::make_shared<Object>(cubeMesh, glm::vec3(-2, 0, -3), glm::vec3(0, 0, 1))); 

	engine.Run();
	engine.Shutdown();
	return 0;
}
