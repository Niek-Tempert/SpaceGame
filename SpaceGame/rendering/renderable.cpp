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

GLuint compile_shader(std::string path, GLenum type) {
	std::string shader_str = load_text(path.c_str());
	const char *shader_code = shader_str.c_str();
	const GLuint shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &shader_code, NULL);
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
	
	glBindBuffer(GL_ARRAY_BUFFER, (GLuint)buffer);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, 0);
}

void dispose(render_object *object) {
	glDeleteProgram(object->program);
	glDeleteShader(object->frag_shader);
	glDeleteShader(object->vert_shader);

	if (object->pos_buffer >= 0) {
		u32 pos_buffer = object->pos_buffer;
		glDeleteBuffers(1, &pos_buffer);
	}

	if (object->col_buffer >= 0) {
		u32 col_buffer = object->col_buffer;
		glDeleteBuffers(1, &col_buffer);
	}

	if (object->norm_buffer >= 0) {
		u32 norm_buffer = object->norm_buffer;
		glDeleteBuffers(1, &norm_buffer);
	}

	if (object->uv_buffer >= 0) {
		u32 uv_buffer = object->uv_buffer;
		glDeleteBuffers(1, &uv_buffer);
	}

	if (object->index_buffer >= 0) {
		u32 index_buffer = object->uv_buffer;
		glDeleteBuffers(1, &index_buffer);
	}
	
	glDeleteVertexArrays(1, &object->vao);

	delete object;
}

MRenderable::~MRenderable() {
	dispose(object);
}

void MRenderable::prepare() {
	if (object) {
		dispose(object);
	}
	
	object = new render_object();
	render_object& object = *this->object;
	
	glGenVertexArrays(1, &object.vao);
	glBindVertexArray(object.vao);
	
	auto verts = get_vertices();
	auto cols = get_colors();
	auto norms = get_normals();
	auto uvs = get_uvs();
	auto indices = get_indices();

	object.vertex_count = (i32)verts.size();
	object.index_count = (i32)indices.size();

	object.pos_buffer = upload_vbuffer(verts);
	object.col_buffer = upload_vbuffer(cols);
	object.norm_buffer = upload_vbuffer(norms);
	object.uv_buffer = upload_vbuffer(uvs);
	object.index_buffer = upload_ibuffer(indices);

	object.index_buffer = compile_shader(get_vertex_shader(), GL_VERTEX_SHADER);
	object.frag_shader = compile_shader(get_fragment_shader(), GL_FRAGMENT_SHADER);

	object.program = glCreateProgram();
	glAttachShader(object.program, object.index_buffer);
	glAttachShader(object.program, object.frag_shader);
	glLinkProgram(object.program);

	const GLint pos_loc = glGetAttribLocation(object.program, "vPos");
	const GLint col_loc = glGetAttribLocation(object.program, "vCol");
	const GLint norm_loc = glGetAttribLocation(object.program, "vNorm");
	const GLint uv_loc = glGetAttribLocation(object.program, "vUV");
	object.mvp_loc = glGetUniformLocation(object.program, "MVP");

	link_vbuffer(object.pos_buffer, pos_loc, 3);
	link_vbuffer(object.col_buffer, col_loc, 3);
	link_vbuffer(object.norm_buffer, norm_loc, 3);
	link_vbuffer(object.uv_buffer, uv_loc, 2);
}

void MRenderable::render(glm::mat4 vp) const {
	if (!object) {
		return;
	}

	const render_object &object = *this->object;
	
	glm::mat4 mvp = vp * get_transform();
	glUseProgram(object.program);
	glUniformMatrix4fv(object.mvp_loc, 1, GL_FALSE, (const GLfloat *)glm::value_ptr(mvp));
	glBindVertexArray(object.vao);

	switch (get_render_type()) {
		case render_type::triangle:
			glDrawArrays(GL_TRIANGLES, 0, object.vertex_count);
			break;

		case render_type::indexed:
			glDrawElements(GL_TRIANGLES, object.index_count, GL_UNSIGNED_INT, (void *)0);
			break;
	}
}