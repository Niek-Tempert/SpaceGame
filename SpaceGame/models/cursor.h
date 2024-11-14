#pragma once

#include "rendering/renderable.h"

#include <glad/gl.h>

#include <glm/gtc/type_ptr.hpp>

class Cursor : public MRenderable {
public:
	const char *get_fragment_shader() const override {
		return "shaders/cursor.frag";
	}

	const char *get_vertex_shader() const override {
		return "shaders/cursor.vert";
	}

	void set_gl_state() const override {
		MRenderable::set_gl_state();
		glLineWidth(4.0f);
	}

	std::vector<vec3f> get_vertices() const override {
		return {
			{ -16.0f, 0.0f, 0.0f },
			{ 16.0f, 0.0f, 0.0f },
			{ 0.0f, -16.0f, 0.0f },
			{ 0.0f, 16.0f, 0.0f }
		};
	}

	void render(DrawCallData *data) const override {
		if (!visible) {
			return;
		}
		
		glUseProgram(object->program);

		set_gl_state();

		glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((float)data->resolution.x / 2.0f, (float)data->resolution.y / 2.0f, 0.0f));
		glm::mat4 ortho = glm::ortho(0.0f, (f32)data->resolution.x, 0.0f, (f32)data->resolution.y, 1.0f, -1.0f);
		glm::mat4 view = ortho * trans;

		GLint view_loc = glGetUniformLocation(object->program, "view");
		glUniformMatrix4fv(view_loc, 1, GL_FALSE, (const GLfloat *)glm::value_ptr(view));

		glBindVertexArray(object->vao);

		glDrawArrays(GL_LINES, 0, object->vertex_count);
	}
};