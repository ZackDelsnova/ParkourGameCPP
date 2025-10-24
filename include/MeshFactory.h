#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Mesh.h"

class MeshFactory {
public:
	static std::shared_ptr<Mesh> CreateCube();
	static std::shared_ptr<Mesh> CreateQuad();
	static std::shared_ptr<Mesh> CreateSphere(int segments = 32, int rings = 32);
	static std::shared_ptr<Mesh> CreateCylinder(float radius = 0.5f, float height = 1.0f ,int segments = 32);
};
