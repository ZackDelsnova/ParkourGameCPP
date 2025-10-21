#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"

class Object {
public:
	Object();
	void Draw(const Shader& shader) const;
	void Destroy();

private:
	GLuint VAO, VBO;
};
