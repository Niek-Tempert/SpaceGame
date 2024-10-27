#include "renderable.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#include "utils/file.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void MRenderable::prepare() {
	auto vertices = get_vertices();
	auto colors = get_colors();
	auto normals = get_normals();
	auto uvs = get_uvs();
	auto indices = get_indices();
	vert_count = vertices.size();
	index_count = indices.size();
	

	GLuint vertex_buffer, color_buffer, normal_buffer, uv_buffer;

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

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	const GLint vpos_location = glGetAttribLocation(program, "vPos");
	const GLint vcol_location = glGetAttribLocation(program, "vCol");
	const GLint vnorm_location = glGetAttribLocation(program, "vNorm");
	const GLint vuv_location = glGetAttribLocation(program, "vUV");

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	if (vpos_location != -1) {
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

	if (vcol_location != -1) {
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

	if (vnorm_location != -1) {
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

	if (vuv_location != -1) {
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
}

void MRenderable::render(glm::mat4 view, glm::mat4 proj) const {
	glm::mat4 model = get_transform();
	glm::mat4 mvp = proj * view * model;

	glUseProgram(program);
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)glm::value_ptr(mvp));
	glBindVertexArray(VAO);

	switch (get_render_type()) {
		case render_type::triangle:
			glDrawArrays(GL_TRIANGLES, 0, vert_count);
			break;

		case render_type::strip:
			glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
			break;
	}
}