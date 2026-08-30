#include "renderable.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>

#include "utils/file.h"

#include <iostream>
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

GLuint compile_shader(const char *path, GLenum type) {
	std::string shader_str = load_text(path);
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

void dispose(RenderObject *object) {
	object->shader.dispose();

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
		u32 index_buffer = object->index_buffer;
		glDeleteBuffers(1, &index_buffer);
	}

	glDeleteVertexArrays(1, &object->vao);

	delete object;
}

MRenderable::~MRenderable() {
	dispose(_render_object);
}

void MRenderable::init() {
	if (_render_object) {
		dispose(_render_object);
	}

	_render_object = new RenderObject();
	RenderObject &object = *this->_render_object;

	glGenVertexArrays(1, &object.vao);
	glBindVertexArray(object.vao);

	auto verts = _get_vertices();
	auto cols = _get_colors();
	auto norms = _get_normals();
	auto uvs = _get_uvs();
	auto indices = _get_indices();

	object.vertex_count = (i32)verts.size();
	object.index_count = (i32)indices.size();

	object.pos_buffer = upload_vbuffer(verts);
	object.col_buffer = upload_vbuffer(cols);
	object.norm_buffer = upload_vbuffer(norms);
	object.uv_buffer = upload_vbuffer(uvs);
	object.index_buffer = upload_ibuffer(indices);

	_render_object->shader = _get_shader();
	const GLint pos_loc = glGetAttribLocation(_render_object->shader.id, "vPos");
	const GLint col_loc = glGetAttribLocation(_render_object->shader.id, "vCol");
	const GLint norm_loc = glGetAttribLocation(_render_object->shader.id, "vNorm");
	const GLint uv_loc = glGetAttribLocation(_render_object->shader.id, "vUV");

	link_vbuffer(object.pos_buffer, pos_loc, sizeof(*verts.data()) / sizeof(f32));
	link_vbuffer(object.col_buffer, col_loc, sizeof(*cols.data()) / sizeof(f32));
	link_vbuffer(object.norm_buffer, norm_loc, sizeof(*norms.data()) / sizeof(f32));
	link_vbuffer(object.uv_buffer, uv_loc, sizeof(*uvs.data()) / sizeof(f32));

	glGenTextures(1, &_render_object->texture_buffer);
	glBindTexture(GL_TEXTURE_2D, _render_object->texture_buffer);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	int width, height, nrChannels;
	u8 *data = stbi_load("assets/images/white_wool.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void MRenderable::render(RenderData *data) const {
	if (!_render_object) {
		return;
	}

	_set_gl_state();
	_before_render(data);
	_render();
}

void MRenderable::_set_gl_state() const {
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glLineWidth(1.0f);
}

void MRenderable::_before_render(RenderData *data) const {
	glm::mat4 model = _get_transform();
	glm::mat4 view = data->view;
	glm::mat4 proj = data->proj;
	glm::mat4 mvp = proj * view * model;

	_render_object->shader.use();
	_render_object->shader.set_mat4("Model", model);
	_render_object->shader.set_mat4("View", view);
	_render_object->shader.set_mat4("Proj", proj);
	_render_object->shader.set_mat4("MVP", mvp);

	glBindTexture(GL_TEXTURE_2D, _render_object->texture_buffer);
	glBindVertexArray(_render_object->vao);
}

void MRenderable::_render() const {
	if (_render_object->index_count > 0) {
		glDrawElements(GL_TRIANGLES, _render_object->index_count, GL_UNSIGNED_INT, (void *)0);
	} else {
		glDrawArrays(GL_TRIANGLES, 0, _render_object->vertex_count);
	}
}
