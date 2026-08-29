#pragma once

#include "rendering/renderable.h"

// TODO: Convert to Quad / Triangle

class Skybox : public MRenderable {
protected:
	void _set_gl_state() const override {
		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);
	}

	glm::mat4x4 _get_transform() const override {
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -0.5f, -0.5f));
		return model;
	}

	std::vector<vec3f> _get_vertices() const override {
		std::vector<vec3f> vertices;
		for (const auto &cube_side : mesh_consts::cube_vertices) {
			for (const auto &vertex : cube_side) {
				vertices.push_back(vertex);
			}
		}
		return vertices;
	}

	std::vector<u32> _get_indices() const override {
		std::vector<u32> indices;
		for (int i = 0; i < 6; ++i) {
			for (auto vertex : mesh_consts::face_indices_inv) {
				indices.push_back(vertex + 4 * i);
			}
		}
		return indices;
	}

	Shader _get_shader() const override {
		return Shader::from_file(SHADER_PATH "skybox.vert", SHADER_PATH "skybox.frag");
	}

	void _before_render(RenderData *data) const override {
		RenderData skybox_data = *data;
		skybox_data.view = glm::mat4(glm::mat3(data->view));
		MRenderable::_before_render(&skybox_data);
	}
};
