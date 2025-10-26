#include "Object.h"

Object::Object(std::shared_ptr<Mesh> mesh, glm::vec3 pos, glm::vec3 color) 
    : mesh(mesh), position(pos), rotation(0.0f), color(color), scale(1.0f) {}

glm::mat4 Object::GetModelMatrix() const {
	glm::mat4 model(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, scale);
	return model;
}

