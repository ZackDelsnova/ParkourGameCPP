#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Mesh.h"

class Object {
public:
	Object(std::shared_ptr<Mesh> mesh, glm::vec3 pos, glm::vec3 color);

	glm::mat4 GetModelMatrix() const;

	std::shared_ptr<Mesh> mesh;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 color;
};
