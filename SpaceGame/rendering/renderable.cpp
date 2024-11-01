#include "renderable.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#include "utils/file.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void MRenderable::prepare() {
	render_type type = get_render_type();
	std::vector<vec3f> vertices = get_vertices();
	std::vector<vec3f> colors = get_colors();
	std::vector<vec3f> normals = get_normals();
	std::vector<vec2f> uvs = get_uvs();
	std::vector<u32> indices = get_indices();
	proxy.vert_count = (u32)vertices.size();
	proxy.index_count = (u32)indices.size();

	GLuint vertex_buffer, color_buffer, normal_buffer, uv_buffer, index_buffer;

	if (!vertices.empty()) {
		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(decltype(vertices)::value_type), vertices.data(), GL_STATIC_DRAW);
	}

	if (!colors.empty()) {
		glGenBuffers(1, &color_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
		glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(decltype(colors)::value_type), colors.data(), GL_STATIC_DRAW);
	}

	if (!normals.empty()) {
		glGenBuffers(1, &normal_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(decltype(normals)::value_type), normals.data(), GL_STATIC_DRAW);
	}

	if (!uvs.empty()) {
		glGenBuffers(1, &uv_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(decltype(uvs)::value_type), uvs.data(), GL_STATIC_DRAW);
	}

	if (!indices.empty()) {
		glGenBuffers(1, &index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(decltype(indices)::value_type), indices.data(), GL_STATIC_DRAW);
	}

	std::string vert_shader_str = load_text(this->get_vertex_shader());
	const char *vert_str_data = vert_shader_str.data(); // TODO: Figure out why this breaks otherwise
	const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vert_str_data, NULL);
	glCompileShader(vertex_shader);

	std::string frag_shader_str = load_text(this->get_fragment_shader());
	const char *frag_str_data = frag_shader_str.data();
	const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &frag_str_data, NULL);
	glCompileShader(fragment_shader);

	// Check for compilation errors
	GLint success;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(vertex_shader, sizeof(infoLog), NULL, infoLog);
		fprintf(stderr, "Shader compilation error:\n%s\n", infoLog);
	}

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(fragment_shader, sizeof(infoLog), NULL, infoLog);
		fprintf(stderr, "Shader compilation error:\n%s\n", infoLog);
	}

	proxy.program = glCreateProgram();
	glAttachShader(proxy.program, vertex_shader);
	glAttachShader(proxy.program, fragment_shader);
	glLinkProgram(proxy.program);

	const GLint vpos_location = glGetAttribLocation(proxy.program, "vPos");
	const GLint vcol_location = glGetAttribLocation(proxy.program, "vCol");
	const GLint vnorm_location = glGetAttribLocation(proxy.program, "vNorm");
	const GLint vuv_location = glGetAttribLocation(proxy.program, "vUV");

	glGenVertexArrays(1, &proxy.vao);
	glBindVertexArray(proxy.vao);
	
	if (!vertices.empty() && vpos_location != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glEnableVertexAttribArray(vpos_location);
		glVertexAttribPointer(
				vpos_location,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				0);
	}

	if (!colors.empty() && vcol_location != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
		glEnableVertexAttribArray(vcol_location);
		glVertexAttribPointer(
				vcol_location,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				0);
	}

	if (!normals.empty() && vnorm_location != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
		glEnableVertexAttribArray(vnorm_location);
		glVertexAttribPointer(
				vnorm_location,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				0);
	}

	if (!uvs.empty() && vuv_location != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, vuv_location);
		glEnableVertexAttribArray(vuv_location);
		glVertexAttribPointer(
				vuv_location,
				2,
				GL_FLOAT,
				GL_FALSE,
				0,
				0);
	}

	if (!indices.empty() && type == render_type::indexed) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	}
}

void MRenderable::render(glm::mat4 view, glm::mat4 proj) const {
	glm::mat4 model = get_transform();
	glm::mat4 mvp = proj * view * model;

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