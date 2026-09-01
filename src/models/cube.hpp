#pragma once

#include "rendering/renderable.h"

class Cube : public MRenderable {
protected:
	std::vector<glm::vec3> getVertices() const override;
	std::vector<glm::vec3> getColors() const override;
	std::vector<u32> getIndices() const override;
	GLuint getShader() const override;
};
