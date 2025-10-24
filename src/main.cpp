#include "Engine.h"
#include "Mesh.h"
#include "MeshFactory.h"
#include "Object.h"
#include <vector>
#include <memory>

int main() {
	Engine engine(1280, 720);
	if (!engine.Init()) {
		return -1;
	}

    std::vector<std::shared_ptr<Object>> worldObjects;

    auto cubeMesh = MeshFactory::CreateCube();
    auto sphereMesh = MeshFactory::CreateSphere();
    auto cylinderMesh = MeshFactory::CreateCylinder();
    auto platformMesh = MeshFactory::CreateCube();
    auto quadMesh = MeshFactory::CreateQuad();

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

	auto cube = std::make_shared<Object>(cubeMesh, glm::vec3(0, 0, -3), glm::vec3(1, 0, 0));
    cube->scale = glm::vec3(2, 1, 4);
    cube->rotation = glm::vec3(1, 90, 1);
    auto sphere = std::make_shared<Object>(sphereMesh, glm::vec3(10, 6, -3), glm::vec3(0, 1, 0));
    sphere->scale = glm::vec3(3, 3, 3);
    auto cylinder = std::make_shared<Object>(cylinderMesh, glm::vec3(-2, 3, 10), glm::vec3(0, 0, 1));
    cylinder->scale = glm::vec3(2, 4, 2);
    auto quad = std::make_shared<Object>(quadMesh, glm::vec3(5, 0, -2), glm::vec3(1, 1, 0));
    quad->scale = glm::vec3(2, 2, 2);

	engine.renderer.AddObject(cube);
    engine.renderer.AddObject(sphere);
    engine.renderer.AddObject(cylinder);
    engine.renderer.AddObject(quad);

	worldObjects.push_back(cube);
    worldObjects.push_back(sphere);
	worldObjects.push_back(cylinder);
    worldObjects.push_back(quad);

	engine.Run();
	engine.Shutdown();
	return 0;
}
