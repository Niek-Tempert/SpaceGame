#pragma once

#include "rendering/renderable.hpp"

class BlockSelect : public Renderable {
public:
	BlockSelect(const Scene* parent);
	void setTransform(glm::mat4 transform);
	void setVisible(bool visible);

	void render();

protected:
	GLuint getShader() const override;
	std::vector<glm::vec3> getVertices() const override;
	glm::mat4x4 getTransform() const override;

private:
	bool m_visible = true;
	glm::mat4 m_transform = glm::mat4(1.0f);
};
