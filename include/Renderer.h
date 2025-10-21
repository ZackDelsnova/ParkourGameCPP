#pragma once
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>
#include "Camera.h"
#include "Shader.h"
#include "Object.h"


class Renderer {
public:
	bool Init(int width, int height);
	void RenderScene(const Camera& camera);
	void AddObject(std::shared_ptr<Object> obj);
	void Shutdown();

private:
	Shader shader;
	std::vector<std::shared_ptr<Object>> objects;
	glm::mat4 projection;
};
