#pragma once

#include "rendering/line_renderable.h"

class BlockSelect : public MLineRenderable {
public:
	void setTransform(glm::mat4 transform);
	void setVisible(bool visible);

protected:
	void setGLState() const override;

	glm::mat4x4 getTransform() const override;
	std::vector<glm::vec3> getVertices() const override;
	GLuint getShader() const override;

	void draw() const override;

private:
	bool m_visible = true;
	glm::mat4 m_transform = glm::mat4(1.0f);
};
