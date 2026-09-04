#pragma once

#include "rendering/renderable.hpp"

class Skybox : public Renderable {
public:
	Skybox(const Scene* parent);
	void render() const override;

protected:
	GLuint getShader() const override;
	std::vector<glm::vec3> getVertices() const override;
	std::vector<u32> getIndices() const override;
	glm::mat4x4 getTransform() const override;
};
