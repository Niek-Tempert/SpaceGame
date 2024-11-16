#pragma once

#include <string>
#include <glm/fwd.hpp>

class Shader {
public:
	unsigned int id;

	Shader();
	Shader(const char *vertex_code, const char *fragment_code);

	static Shader from_file(const char *vertexPath, const char *fragmentPath);

	void use();
	void dispose();

	void set_bool(const std::string &name, bool value) const;

	void set_int(const std::string &name, int value) const;

	void set_float(const std::string &name, float value) const;
	
	void set_mat4(const std::string &name, glm::mat4 value) const;

private:
	void check_compile_errors(unsigned int shader, std::string type);
};
