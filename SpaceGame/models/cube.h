#pragma once
#include "rendering/renderable.h"
#include "utils/mesh_consts.h"

class Cube : public MRenderable {
public:
	const std::string get_vertex_shader() const override {
		return "shaders/vertex/basic.glsl";
	}

	const std::string get_fragment_shader() const override {
		return "shaders/fragment/basic.glsl";
	}

	const std::vector<vec3f> get_vertices() const override {
		std::vector<vec3f> vertices;
		for (const auto &cube_side : mesh_consts::cube_vertices) {
			for (const auto &vertex : cube_side) {
				vertices.push_back(vertex);
			}
		}
		return vertices;
	}

	const std::vector<vec3f> get_colors() const override {
		std::vector<vec3f> colors;
		for (const auto &cube_side : mesh_consts::cube_vertices) {
			for (const auto &vertex : cube_side) {
				colors.push_back(vertex);
			}
		}
		return colors;
	}

	const std::vector<u32> get_indices() const override {
		std::vector<u32> indices;
		for (int i = 0; i < 6; ++i) {
			for (auto vertex : mesh_consts::cube_indices) {
				indices.push_back(vertex + 4 * i);
			}
		}
		return indices;
	}
};
