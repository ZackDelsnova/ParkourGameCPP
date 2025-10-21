#include "Shader.h"

bool Shader::LoadFromFiles(const std::vector<std::string>& files) {
	GLuint vertexShader = 0, fragmentShader = 0, geometryShader = 0;

	for (const auto& path : files) {
		std::string lower = path;
		std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

		GLenum type;
		if (lower.ends_with(".vert") || lower.ends_with("vertex.glsl")) {
			type = GL_VERTEX_SHADER;
		} else if (lower.ends_with(".frag") || lower.ends_with("fragment.glsl")) {
			type = GL_FRAGMENT_SHADER;
		} else if (lower.ends_with(".geom")) {
			type = GL_GEOMETRY_SHADER;
		} else {
			continue; // unsupported shader type, skip it
		}

		std::string source = readFile(path);
		GLuint shader;
		if (!compileShader(shader, source, type)) {
			return false;
		}

		if (type == GL_VERTEX_SHADER) vertexShader = shader;
		if (type == GL_FRAGMENT_SHADER) fragmentShader = shader;
		if (type == GL_GEOMETRY_SHADER) geometryShader = shader;
	}

	program = glCreateProgram();
	if (vertexShader) glAttachShader(program, vertexShader);
	if (fragmentShader) glAttachShader(program, fragmentShader);
	if (geometryShader) glAttachShader(program, geometryShader);

	glLinkProgram(program);
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return false;
	}

	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return false;
	}

	if (vertexShader) glDeleteShader(vertexShader);
	if (fragmentShader) glDeleteShader(fragmentShader);
	if (geometryShader) glDeleteShader(geometryShader);
	return true;
}

void Shader::Use() const {
	glUseProgram(program);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value) const {
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const {
	glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}

bool Shader::compileShader(GLuint& shader, const std::string& source, GLenum type) {
	shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}

	return true;
}

std::string Shader::readFile(const std::string& path) {
	std::ifstream file(path);
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}
