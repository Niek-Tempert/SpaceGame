#include "shader.h"

#include "nixelib/nixelib.h"

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <glm/fwd.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

static const char *errorVertexCode = "#version 330\n uniform mat4 MVP; in vec3 vPos; void main() { gl_Position = MVP * vec4(vPos, 1.0); };";
static const char *errorFragmentCode = "#version 330\n out vec4 fragment; void main() { fragment = vec4(1.0, 0.0, 1.0, 1.0); };";

FORCEINLINE std::string load_text(const char *path) {
	std::string content;
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(path);
		std::stringstream file_stream;
		file_stream << file.rdbuf();
		file.close();
		content = file_stream.str();
	} catch (std::ifstream::failure &e) {
		std::cerr << "ERROR::FILE::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}
	
	return content;
}

std::string preprocess_shader(std::string source) {
	std::string result = source;
	size_t pos = 0;
	while ((pos = result.find("#include", pos)) != std::string::npos) {
		size_t start = result.find("\"", pos);
		size_t end = result.find("\"", start + 1);
		std::string includePath = "shaders/" + result.substr(start + 1, end - start - 1);
		std::string includeSource = load_text(includePath.c_str());
		result.replace(pos, end - pos + 1, includeSource);
	}
	return result;
}

Shader::Shader() : Shader(errorVertexCode, errorFragmentCode) {}

Shader::Shader(const char *vertex_code, const char *fragment_code) {
	u32 vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertex_code, NULL);
	glCompileShader(vertex);
	check_compile_errors(vertex, "VERTEX");

	u32 fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragment_code, NULL);
	glCompileShader(fragment);
	check_compile_errors(fragment, "FRAGMENT");

	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	check_compile_errors(id, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader Shader::from_file(const char *vertexPath, const char *fragmentPath) {
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode = load_text(vertexPath);
	std::string fragmentCode = load_text(fragmentPath);

	vertexCode = preprocess_shader(vertexCode);
	fragmentCode = preprocess_shader(fragmentCode);

	return { vertexCode.c_str(), fragmentCode.c_str() };
}


void Shader::use() {
	glUseProgram(id);
}

void Shader::dispose() {
	glDeleteProgram(id);
}

void Shader::set_bool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::set_int(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set_mat4(const std::string &name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, (const GLfloat *)glm::value_ptr(value));
}

void Shader::check_compile_errors(unsigned int shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}