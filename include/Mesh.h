#pragma once
#include <glad/glad.h>
#include <vector>

class Mesh {
public:
	unsigned int VAO, VBO;
	int vertexCount;

	Mesh(const std::vector<float>& vertices);
	void Draw() const;
	void Cleanup();
};
