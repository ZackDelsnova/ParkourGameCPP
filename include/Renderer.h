#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include <string>

class Renderer {
public:
	void Init(int width, int height);
	void Draw(const Camera& camera);
	void Cleanup();
private:
	unsigned int VAO, VBO; // Vertex Array Object and Vertex Buffer Object
	unsigned int shaderProgram;
	glm::mat4 projection;

	unsigned int LoadShader(const std::string& vertexPath, const std::string& fragmentPath);
};
