#pragma once

#include "rendering/renderable.h"

#include <glm/ext/matrix_transform.hpp>

class CubeLines : public MRenderable {
protected:
	RenderType get_render_type() const override {
		return RenderType::lines;
	}

	void set_gl_state() const override {
		MRenderable::set_gl_state();
		glDisable(GL_DEPTH_TEST);
		glLineWidth(4.0f);
	}

	const char *get_vertex_shader() const override {
		return "shaders/black.vert";
	}

	const char *get_fragment_shader() const override {
		return "shaders/black.frag";
	}

	std::vector<vec3f> get_vertices() const override {
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
};