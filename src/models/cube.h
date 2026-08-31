#pragma once
#include "rendering/renderable.h"
#include "utils/mesh_consts.h"
#include <common/helpers.h>
#include <common/glutils.h>
#include "glad/glad.h"

class Cube : public MRenderable {
protected:
	std::vector<glm::vec3> getVertices() const override {
		std::vector<glm::vec3> vertices;
		for (const auto &cube_side : mesh_consts::cubeVerts) {
			for (const auto &vertex : cube_side) {
				vertices.push_back(vertex);
			}
		}
		return vertices;
	}

	std::vector<glm::vec3> getColors() const override {
		std::vector<glm::vec3> colors;
		for (const auto &cube_side : mesh_consts::cubeVerts) {
			for (const auto &vertex : cube_side) {
				colors.push_back(vertex);
			}
		}
		return colors;
	}

	std::vector<u32> getIndices() const override {
		std::vector<u32> indices;
		for (int i = 0; i < 6; ++i) {
			for (auto vertex : mesh_consts::faceIndices) {
				indices.push_back(vertex + 4 * i);
			}
		}
		return indices;
	}

	GLuint getShader() const override {
		GLuint shader = 0;
		if (shaderLoadVF(&shader, SHADER_PATH "unlit.vert", SHADER_PATH "unlit.frag")) throw;
		return shader;
	}
};
