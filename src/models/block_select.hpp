#pragma once

#include "rendering/line_renderable.h"

class BlockSelect : public MLineRenderable {
public:
	bool m_visible;
	glm::mat4 m_transform;

	BlockSelect() : m_visible(true), m_transform(glm::mat4(1.0f)) {}
	
protected:
	void setGLState() const override;

	glm::mat4x4 getTransform() const override;
	std::vector<glm::vec3> getVertices() const override;
	GLuint getShader() const override;
	
	void draw() const override;
};