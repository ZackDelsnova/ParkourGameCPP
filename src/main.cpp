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

	auto floor1 = std::make_shared<Object>(platformMesh, glm::vec3(0, -1, 0), glm::vec3(0.5f, 0.5f, 0.5f));
	floor1->scale = glm::vec3(100, 1, 100);

    auto floor2 = std::make_shared<Object>(platformMesh, glm::vec3(10, 5, 0), glm::vec3(0.5f, 0.5f, 0.6f));
    floor2->scale = glm::vec3(10, 1, 10);

    auto floor3 = std::make_shared<Object>(platformMesh, glm::vec3(0, 2, 10), glm::vec3(0.5f, 0.5f, 0.7f));
    floor3->scale = glm::vec3(10, 1, 10);

	engine.renderer.AddObject(floor1);
	worldObjects.push_back(floor1);
    engine.renderer.AddObject(floor2);
    worldObjects.push_back(floor2);
    engine.renderer.AddObject(floor3);
    worldObjects.push_back(floor3);

	auto cube1 = std::make_shared<Object>(cubeMesh, glm::vec3(0, 0, -3), glm::vec3(1, 0, 0));
    cube1->scale = glm::vec3(2, 1, 4);
    cube1->rotation = glm::vec3(1, 90, 1);
    auto cube2 = std::make_shared<Object>(cubeMesh, glm::vec3(10, 6, -3), glm::vec3(0, 1, 0));
    auto cube3 = std::make_shared<Object>(cubeMesh, glm::vec3(-2, 3, 10), glm::vec3(0, 0, 1));

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
