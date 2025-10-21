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

    std::vector<std::shared_ptr<Object>> worldObjects;

	auto cubeMesh = std::make_shared<Mesh>(cubeVerts);
    auto platformMesh = std::make_shared<Mesh>(cubeVerts);

	auto floor = std::make_shared<Object>(platformMesh, glm::vec3(0, -1, 0), glm::vec3(0.5f, 0.5f, 0.5f));
	floor->scale = glm::vec3(10, 1, 10);
	engine.renderer.AddObject(floor);
	worldObjects.push_back(floor);

	auto cube1 = std::make_shared<Object>(cubeMesh, glm::vec3(0, 0, -3), glm::vec3(1, 0, 0));
    auto cube2 = std::make_shared<Object>(cubeMesh, glm::vec3(2, 0, -3), glm::vec3(0, 1, 0));
    auto cube3 = std::make_shared<Object>(cubeMesh, glm::vec3(-2, 0, -3), glm::vec3(0, 0, 1));

	engine.renderer.AddObject(cube1);
    engine.renderer.AddObject(cube2);
    engine.renderer.AddObject(cube3);

	worldObjects.push_back(cube1);
    worldObjects.push_back(cube2);
	worldObjects.push_back(cube3);

	engine.Run();
	engine.Shutdown();
	return 0;
}
