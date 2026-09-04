#pragma once

#include "rendering/renderable.hpp"

class Cube : public Renderable {
protected:
	Cube(const Scene* parent);
	std::vector<glm::vec3> getVertices() const override;
	std::vector<glm::vec3> getColors() const override;
	std::vector<u32> getIndices() const override;
	GLuint getShader() const override;
};
