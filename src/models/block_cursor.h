#pragma once

#include "rendering/line_renderable.h"
#include <common/helpers.h>
#include <common/glutils.h>

class BlockCursor : public MLineRenderable {
public:
	bool m_visible;
	glm::mat4 m_transform;

	BlockCursor() : m_visible(true), m_transform(glm::mat4(1.0f)) {}
	
protected:
	void _set_gl_state() const override {
		MRenderable::_set_gl_state();
		glDisable(GL_DEPTH_TEST);
		glLineWidth(4.0f);
	}

	glm::mat4x4 _get_transform() const override {
		return m_transform;
	}

	std::vector<glm::vec3> _get_vertices() const override {
		return {
			{ 1, 0, 1 }, { 1, 1, 1 }, { 1, 1, 0 }, { 1, 0, 0 },
			{ 0, 0, 0 }, { 0, 1, 0 }, { 0, 1, 1 }, { 0, 0, 1 },
			{ 0, 1, 1 }, { 0, 1, 0 }, { 1, 1, 0 }, { 1, 1, 1 },
			{ 0, 0, 0 }, { 0, 0, 1 }, { 1, 0, 1 }, { 1, 0, 0 },
			{ 0, 0, 1 }, { 0, 1, 1 }, { 1, 1, 1 }, { 1, 0, 1 },
			{ 1, 0, 0 }, { 1, 1, 0 }, { 0, 1, 0 }, { 0, 0, 0 },
			{ 0, 0, 0 }, { 1, 0, 0 }, { 0, 0, 1 }, { 1, 0, 1 },
			{ 0, 1, 0 }, { 1, 1, 0 }, { 0, 1, 1 }, { 1, 1, 1 }
		};
	}

	GLuint _get_shader() const override {
		GLuint shader = 0;
		if (shaderLoadVF(&shader, SHADER_PATH "black.vert", SHADER_PATH "black.frag")) throw;
		return shader;
	}

	void _render() const override {
		if (!m_visible) {
			return;
		}
		
		MLineRenderable::_render();
	}
};