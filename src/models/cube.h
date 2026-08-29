#pragma once
#include "rendering/renderable.h"
#include "utils/mesh_consts.h"
#include <common/helpers.h>

class Cube : public MRenderable {
protected:
	std::vector<vec3f> _get_vertices() const override {
		std::vector<vec3f> vertices;
		for (const auto &cube_side : mesh_consts::cube_vertices) {
			for (const auto &vertex : cube_side) {
				vertices.push_back(vertex);
			}
		}
		return vertices;
	}

	std::vector<vec3f> _get_colors() const override {
		std::vector<vec3f> colors;
		for (const auto &cube_side : mesh_consts::cube_vertices) {
			for (const auto &vertex : cube_side) {
				colors.push_back(vertex);
			}
		}
		return colors;
	}

	std::vector<u32> _get_indices() const override {
		std::vector<u32> indices;
		for (int i = 0; i < 6; ++i) {
			for (auto vertex : mesh_consts::face_indices) {
				indices.push_back(vertex + 4 * i);
			}
		}
		return indices;
	}

	Shader _get_shader() const override {
		return Shader::from_file(SHADER_PATH "unlit.vert", SHADER_PATH "unlit.frag");
	}
};
