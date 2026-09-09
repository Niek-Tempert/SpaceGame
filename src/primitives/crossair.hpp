#pragma once

#include "rendering/renderable.hpp"
#include "providers/canvas_provider.hpp"

class Crossair 
	: public Renderable
	, public CanvasProvider {
public:
	Crossair(const Scene* parent);
	
protected:
	std::vector<glm::vec3> getVertices() const override;
	GLuint getShader() const override;
	void setGLState() const override;

	glm::mat4 getTransform() const override;
	glm::mat4 getView() const override;
	glm::mat4 getProj() const override;
};
