#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

class Shader {
public:
	bool LoadFromFiles(const std::vector<std::string>& files);
	void Use() const;
	void SetMat4(const std::string& name, const glm::mat4& value) const;
	// other setter

private:
	GLuint program;
	bool compileShader(GLuint& shader, const std::string& source, GLenum type);
	std::string readFile(const std::string& path);
};
