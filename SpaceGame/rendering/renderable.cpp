#include "renderable.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#include "utils/file.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

template <typename T>
GLint upload_vbuffer(std::vector<T> data) {
	if (data.empty()) {
		return -1;
	}
	
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*data.data()) * data.size(), data.data(), GL_STATIC_DRAW);
	return (GLint)buffer;
}

template <typename T>
GLint upload_ibuffer(std::vector<T> data) {
	if (data.empty()) {
		return -1;
	}
	
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*data.data()) * data.size(), data.data(), GL_STATIC_DRAW);
	return (GLint)buffer;
}

bool has_succeeded(GLuint shader) {
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		fprintf(stderr, "Shader compilation error:\n%s\n", infoLog);
	}

	return success;
}

GLuint compile_shader(const std::string &path, GLenum type) {
	std::string shader = load_text(path);
	const char *shader_data = shader.data(); // TODO: Figure out why this breaks otherwise
	const GLuint shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &shader_data, NULL);
	glCompileShader(shader_id);

	bool success = has_succeeded(shader_id);
	if (success) {
		return shader_id;
	}
	
	const char *fallback;
	switch (type) {
		default: // GL_VERTEX_SHADER
			fallback = "#version 330\n uniform mat4 MVP; in vec3 vPos; void main() { gl_Position = MVP * vec4(vPos, 1.0); };";
			break;

		case GL_FRAGMENT_SHADER:
			fallback = "#version 330\n out vec4 fragment; void main() { fragment = vec4(1.0, 0.0, 1.0, 1.0); };";
			break;
	}
	glShaderSource(shader_id, 1, &fallback, NULL);
	glCompileShader(shader_id);
	has_succeeded(shader_id);

	return shader_id;
}

void link_vbuffer(GLint buffer, GLuint location, GLint size) {
	if (buffer < 0 || location < 0) {
		return;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, 0);
}

void link_ibuffer(GLint buffer) {
	if (buffer < 0) {
		return;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

void MRenderable::prepare() {
	auto verts = get_vertices();
	auto cols = get_colors();
	auto norms = get_normals();
	auto uvs = get_uvs();
	auto indices = get_indices();

	proxy.vert_count = (i32)verts.size();
	proxy.index_count = (i32)indices.size();

	GLint pos_buffer = upload_vbuffer(verts);
	GLint col_buffer = upload_vbuffer(cols);
	GLint norm_buffer = upload_vbuffer(norms);
	GLint uv_buffer = upload_vbuffer(uvs);
	GLint index_buffer = upload_ibuffer(indices);

	const GLuint vert_shader = compile_shader(get_vertex_shader(), GL_VERTEX_SHADER);
	const GLuint frag_shader = compile_shader(get_fragment_shader(), GL_FRAGMENT_SHADER);

	u32 program = glCreateProgram();
	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);
	glLinkProgram(program);
	proxy.program = program;

	const GLint pos_loc = glGetAttribLocation(program, "vPos");
	const GLint col_loc = glGetAttribLocation(program, "vCol");
	const GLint norm_loc = glGetAttribLocation(program, "vNorm");
	const GLint uv_loc = glGetAttribLocation(program, "vUV");

	u32 vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	proxy.vao = vao;

	link_vbuffer(pos_buffer, pos_loc, 3);
	link_vbuffer(col_buffer, col_loc, 3);
	link_vbuffer(norm_buffer, norm_loc, 3);
	link_vbuffer(uv_buffer, uv_loc, 2);
	link_ibuffer(index_buffer);
}

void MRenderable::render(glm::mat4 vp) const {
	glm::mat4 mvp = vp * get_transform();
	glUseProgram(proxy.program);
	glUniformMatrix4fv(proxy.mvp_location, 1, GL_FALSE, (const GLfloat *)glm::value_ptr(mvp));
	glBindVertexArray(proxy.vao);

	switch (get_render_type()) {
		case render_type::triangle:
			glDrawArrays(GL_TRIANGLES, 0, proxy.vert_count);
			break;

		case render_type::indexed:
			glDrawElements(GL_TRIANGLES, proxy.index_count, GL_UNSIGNED_INT, 0);
			break;
	}
}