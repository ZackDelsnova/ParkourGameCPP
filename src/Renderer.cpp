#include "Renderer.h"

bool Renderer::Init(int width, int height) {
	glViewport(0, 0, width, height);
	gladLoadGL();
	glEnable(GL_DEPTH_TEST);

	shader.LoadFromFiles({ "shaders/basic.vert", "shaders/basic.frag" });

	projection = glm::perspective(glm::radians(70.0f),
		(float)width / (float)height, 0.1f, 100.0f);

	return true;
}

void Renderer::RenderScene(const Camera& camera) {
	glClearColor(0.5f, 0.2f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	shader.Use();
	shader.SetMat4("projection", projection);
	shader.SetMat4("view", camera.GetViewMatrix());

	for (auto& obj : objects) {
		shader.SetMat4("model", obj->GetModelMatrix());
		shader.SetVec4("objectColor", glm::vec4(obj->color, 1.0f));
		obj->mesh->Draw();
	}
}

void Renderer::AddObject(std::shared_ptr<Object> obj) {
	objects.push_back(obj);
}

void Renderer::Shutdown() {
	for (auto& obj : objects) {
		obj->mesh->Cleanup();
	}
}