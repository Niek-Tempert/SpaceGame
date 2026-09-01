#pragma once

#include "rendering/renderable.h"

class Skybox : public MRenderable {
protected:
	void setGLState() const override;
	
	glm::mat4x4 getTransform() const override;
	std::vector<glm::vec3> getVertices() const override;
	std::vector<u32> getIndices() const override;
	GLuint getShader() const override;
	
	void beforeRender(RenderData *data) const override;
};
