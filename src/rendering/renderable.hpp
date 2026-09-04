#pragma once

#include <glad/glad.h>

#include <vector>
#include <glm/mat4x4.hpp>
#include <common/types.h>
#include <providers/camera_provider.hpp>

class Scene;

class IRenderable {
public:
	virtual void render() const = 0;
};

class Renderable 
	: public IRenderable
	, public CameraProvider {
public:
	Renderable(const Scene* parent);
	virtual ~Renderable();
	
	void render() const override;

protected:
	virtual GLuint getShader() const;
	virtual std::vector<glm::vec3> getVertices() const;
	virtual std::vector<glm::vec3> getColors() const;
	virtual std::vector<glm::vec3> getNormals() const;
	virtual std::vector<glm::vec2> getUVs() const;
	virtual std::vector<u32> getIndices() const;
	virtual glm::mat4x4 getTransform() const;

	void setRenderType(GLenum type);

private:
	GLuint m_vao;
	GLuint m_shader;
	GLuint m_texture;
	
	u32 m_vertCt;
	u32 m_idxCt;

	GLuint m_vertBuff;
	GLuint m_colBuff;
	GLuint m_normBuff;
	GLuint m_uvBuff;
	GLuint m_idxBuff;

	GLenum m_renderType;
};
