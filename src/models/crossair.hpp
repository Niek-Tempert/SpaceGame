#pragma once

#include "rendering/line_renderable.h"

class Crossair : public MLineRenderable {
public:
	void setGLState() const override;
	
	std::vector<glm::vec3> getVertices() const override;
	GLuint getShader() const override;

	void beforeRender(RenderData *data) const override;
};
