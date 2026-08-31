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
	void setGLState() const override {
		MRenderable::setGLState();
		glDisable(GL_DEPTH_TEST);
		glLineWidth(4.0f);
	}

	glm::mat4x4 getTransform() const override {
		return m_transform;
	}

	std::vector<glm::vec3> getVertices() const override {
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

	GLuint getShader() const override {
		GLuint shader = 0;
		if (shaderLoadVF(&shader, SHADER_PATH "black.vert", SHADER_PATH "black.frag")) throw;
		return shader;
	}

	void draw() const override {
		if (!m_visible) {
			return;
		}
		
		MLineRenderable::draw();
	}
};