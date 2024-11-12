#include "renderable.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

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

void dispose(render_object *object) {
	glDeleteProgram(object->program);

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

	GLuint vert_shader = compile_shader(get_vertex_shader(), GL_VERTEX_SHADER);
	GLuint frag_shader = compile_shader(get_fragment_shader(), GL_FRAGMENT_SHADER);

	// int t_width, t_height, t_channels;
	// unsigned char *data = stbi_load(get_texture(), &t_width, &t_height, &t_channels, 0); 

	object.program = glCreateProgram();
	glAttachShader(object.program, vert_shader);
	glAttachShader(object.program, frag_shader);
	glLinkProgram(object.program);

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	const GLint pos_loc = glGetAttribLocation(object.program, "vPos");
	const GLint col_loc = glGetAttribLocation(object.program, "vCol");
	const GLint norm_loc = glGetAttribLocation(object.program, "vNorm");
	const GLint uv_loc = glGetAttribLocation(object.program, "vUV");
	object.mvp_loc = glGetUniformLocation(object.program, "MVP");
	object.model_loc = glGetUniformLocation(object.program, "Model");
	object.view_loc = glGetUniformLocation(object.program, "View");
	object.proj_loc = glGetUniformLocation(object.program, "Proj");

	link_vbuffer(object.pos_buffer, pos_loc, 3);
	link_vbuffer(object.col_buffer, col_loc, 3);
	link_vbuffer(object.norm_buffer, norm_loc, 3);
	link_vbuffer(object.uv_buffer, uv_loc, 2);
}

void MRenderable::render(draw_call_data* data) const {
	if (!object || !visible) {
		return;
	}

	set_gl_state();

	glm::mat4 model = get_transform();
	glm::mat4 view = data->view;
	glm::mat4 proj = data->proj;
	
	glUseProgram(object->program);

	if (object->model_loc >= 0) {
		glUniformMatrix4fv(object->model_loc, 1, GL_FALSE, (const GLfloat *)glm::value_ptr(model));
	}

	if (object->view_loc >= 0) {
		glUniformMatrix4fv(object->view_loc, 1, GL_FALSE, (const GLfloat *)glm::value_ptr(view));
	}

	if (object->proj_loc >= 0) {
		glUniformMatrix4fv(object->proj_loc, 1, GL_FALSE, (const GLfloat *)glm::value_ptr(proj));
	}

	if (object->mvp_loc >= 0) {
		glm::mat4 mvp = proj * view * model;
		glUniformMatrix4fv(object->mvp_loc, 1, GL_FALSE, (const GLfloat *)glm::value_ptr(mvp));
	}
	
	glBindVertexArray(object->vao);

	switch (get_render_type()) {
		case render_type::triangles:
			glDrawArrays(GL_TRIANGLES, 0, object->vertex_count);
			break;

		case render_type::indexed:
			glDrawElements(GL_TRIANGLES, object->index_count, GL_UNSIGNED_INT, (void *)0);
			break;

		case render_type::lines:
			glDrawArrays(GL_LINES, 0, object->vertex_count);
			break;
	}
}

void MRenderable::set_gl_state() const {
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glLineWidth(1.0f);
}