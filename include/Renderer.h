#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Shader.h"
#include "Object.h"
#include <vector>

class Renderer {
public:
	bool Init(int width, int height);
	void RenderScene(const Camera& camera);
	void AddObject(const Object& obj);
	void Shutdown();
private:
	Shader shader;
	std::vector<Object> objects;
	glm::mat4 projection;
};
