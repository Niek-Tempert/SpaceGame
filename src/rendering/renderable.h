#pragma once

#include "glad/glad.h"

#include <vector>
#include <glm/mat4x4.hpp>
#include <common/types.h>

struct RenderData {
	glm::mat4 view;
	glm::mat4 proj;

	glm::uvec2 resolution;
};

struct RenderObject {
	u32 vao;
	GLuint shader;

	i32 vertCt;
	i32 idxCt;

	i32 posBuff;
	i32 colBuff;
	i32 normBuff;
	i32 uvBuff;
	i32 idxBuff;

	u32 texBuff;
};

class IRenderable {
public:
	virtual ~IRenderable() = default;
	
	virtual void init() = 0;
	virtual void render(RenderData *data) const = 0;
};

class MRenderable : public IRenderable {
public:
	MRenderable() : m_renderObject(NULL) {}
	~MRenderable() override;
	
	void init() override;
	void render(RenderData *data) const final;

protected:
	virtual void setGLState() const;

	virtual glm::mat4x4 getTransform() const { return glm::mat4(1.0f); }
	virtual std::vector<glm::vec3> getVertices() const { return {}; }
	virtual std::vector<glm::vec3> getColors() const { return {}; }
	virtual std::vector<glm::vec3> getNormals() const { return {}; }
	virtual std::vector<glm::vec2> getUVs() const { return {}; }
	virtual std::vector<u32> getIndices() const { return {}; }
	virtual GLuint getShader() const { return 0; }

	virtual void beforeRender(RenderData *data) const;
	virtual void draw() const;

	RenderObject* m_renderObject;
};
