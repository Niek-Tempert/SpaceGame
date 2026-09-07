#pragma once

#include "rendering/renderable.hpp"

class Crossair : public Renderable {
public:
	Crossair(const Scene* parent);
	
protected:
	std::vector<glm::vec3> getVertices() const override;
	GLuint getShader() const override;
	void setState() const override;
};
