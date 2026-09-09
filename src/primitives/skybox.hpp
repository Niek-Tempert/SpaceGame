#pragma once

#include <rendering/renderable.hpp>

class Scene;

class Skybox : public Renderable {
public:
	Skybox(const Scene* parent);
	
protected:
	GLuint getShader() const override;
	std::vector<glm::vec3> getVertices() const override;
	std::vector<u32> getIndices() const override;
	glm::mat4 getTransform() const override;
	void setGLState() const override;

	glm::mat4 getView() const override;
};
