#pragma once

#include "rendering/renderable.h"
#include "utils/mesh_consts.h"

#include <common/helpers.h>
#include <common/glutils.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// TODO: Convert to Quad / Triangle

class Skybox : public MRenderable {
protected:
	void setGLState() const override {
		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);
	}

	glm::mat4x4 getTransform() const override {
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -0.5f, -0.5f));
		return model;
	}

	std::vector<glm::vec3> getVertices() const override {
		std::vector<glm::vec3> vertices;
		for (const auto &cube_side : MeshConsts::cubeVerts) {
			for (const auto &vertex : cube_side) {
				vertices.push_back(vertex);
			}
		}
		return vertices;
	}

	std::vector<u32> getIndices() const override {
		std::vector<u32> indices;
		for (int i = 0; i < 6; ++i) {
			for (auto vertex : MeshConsts::faceIndicesInv) {
				indices.push_back(vertex + 4 * i);
			}
		}
		return indices;
	}

	GLuint getShader() const override {
		GLuint shader = 0;
		if (shaderLoadVF(&shader, SHADER_PATH "skybox.vert", SHADER_PATH "skybox.frag")) throw;
		return shader;
	}

	void beforeRender(RenderData *data) const override {
		RenderData skyboxData = *data;
		skyboxData.view = glm::mat4(glm::mat3(data->view));
		MRenderable::beforeRender(&skyboxData);
	}
};
