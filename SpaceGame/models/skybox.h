#pragma once

#include "rendering/renderable.h"

// TODO: Convert to Quad / Triangle

class Skybox : public MRenderable {
protected:
	const char *get_vertex_shader() const override {
		return "shaders/skybox.vert";
	}

	const char *get_fragment_shader() const override {
		return "shaders/skybox.frag";
	}

	glm::mat4x4 get_transform() const override {
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -0.5f, -0.5f));
		return model;
	}

	bool get_depth_test() const override {
		return false;
	}

	std::vector<vec3f> get_vertices() const override {
		std::vector<vec3f> vertices;
		for (const auto &cube_side : mesh_consts::cube_vertices) {
			for (const auto &vertex : cube_side) {
				vertices.push_back(vertex);
			}
		}
		return vertices;
	}

	std::vector<u32> get_indices() const override {
		std::vector<u32> indices;
		for (int i = 0; i < 6; ++i) {
			for (auto vertex : mesh_consts::face_indices_inv) {
				indices.push_back(vertex + 4 * i);
			}
		}
		return indices;
	}

	void render(draw_call_data *data) const override {
		draw_call_data skybox_data = *data;
		skybox_data.view = glm::mat4(glm::mat3(data->view));
		MRenderable::render(&skybox_data);
	}
};
