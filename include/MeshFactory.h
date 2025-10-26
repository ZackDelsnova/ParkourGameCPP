#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Mesh.h"

class MeshFactory {
public:
	static std::shared_ptr<Mesh> CreateCube(float size = 5.0f);
	static std::shared_ptr<Mesh> CreateQuad(float size = 5.0f);
	static std::shared_ptr<Mesh> CreateSphere(int segments = 32, int rings = 32, float radius = 0.5f);
	static std::shared_ptr<Mesh> CreateCylinder(float radius = 0.5f, float height = 1.0f ,int segments = 32);
	static std::shared_ptr<Mesh> CreateCapsule(int segments = 32, int rings = 32, float radius = 0.5f, float height = 2.0f);
};
