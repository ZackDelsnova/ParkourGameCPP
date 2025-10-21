#include "Renderer.h"

bool Renderer::Init(int width, int height) {
	glViewport(0, 0, width, height);
	gladLoadGL();
	glEnable(GL_DEPTH_TEST);
	shader.LoadFromFiles({ "shaders/basic.vert", "shaders/basic.frag" });
	projection = glm::perspective(glm::radians(70.0f),
		(float)width / (float)height, 0.1f, 100.0f);

	// add one cube	for testing
	objects.emplace_back();
	return true;
}

void Renderer::RenderScene(const Camera& camera) {
	glClearColor(0.05f, 0.05f, 0.07f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.Use();
	shader.SetMat4("projection", projection);
	shader.SetMat4("view", camera.GetViewMatrix());

	for (auto& obj : objects) {
		glm::mat4 model = glm::mat4(1.0f);
		shader.SetMat4("model", model);
		obj.Draw(shader);
	}
}

void Renderer::AddObject(const Object& obj) {
	objects.push_back(obj);
}

void Renderer::Shutdown() {
	for (auto& obj : objects) {
		obj.Destroy();
	}
}