#pragma once

#include "rendering/renderable.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

class Cursor : public MLineRenderable {
public:
	void _set_gl_state() const override {
		MRenderable::_set_gl_state();
		glLineWidth(4.0f);
	}

	std::vector<vec3f> _get_vertices() const override {
		return {
			{ -16.0f, 0.0f, 0.0f },
			{ 16.0f, 0.0f, 0.0f },
			{ 0.0f, -16.0f, 0.0f },
			{ 0.0f, 16.0f, 0.0f }
		};
	}

	Shader _get_shader() const override {
		return Shader::from_file(SHADER_PATH "cursor.vert", SHADER_PATH "cursor.frag");
	}

	void _before_render(RenderData *data) const override {
		_render_object->shader.use();

		glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((float)data->resolution.x / 2.0f, (float)data->resolution.y / 2.0f, 0.0f));
		glm::mat4 ortho = glm::ortho(0.0f, (f32)data->resolution.x, 0.0f, (f32)data->resolution.y, 1.0f, -1.0f);
		glm::mat4 view = ortho * trans;

		_render_object->shader.set_mat4("view", view);

		glBindVertexArray(_render_object->vao);
	}
};