#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <common/types.h>

#include <providers/camera_provider.hpp>

enum class RenderConfig {
	Tris = 0 << 0,
	Lines = 1 << 0,
	Indexed = 1 << 1
};

class IRenderable {
public:
	virtual void render() const = 0;
};

class Renderable 
	: public IRenderable
	, public CameraProvider {
public:
	Renderable(const CameraProvider* parent, u32 config = (u32)RenderConfig::Tris | (u32)RenderConfig::Indexed);
	virtual ~Renderable();
	
	void render() const override;
	void remesh();

protected:
	virtual void setGLState() const;
	virtual GLuint getShader() const;
	virtual std::vector<glm::vec3> getVertices() const;
	virtual std::vector<glm::vec3> getColors() const;
	virtual std::vector<glm::vec3> getNormals() const;
	virtual std::vector<glm::vec2> getUVs() const;
	virtual std::vector<u32> getIndices() const;
	virtual glm::mat4 getTransform() const;

private:
	void setup();
	void dispose();

	GLuint m_vao;
	GLuint m_shader;
	
	u32 m_vertCt;
	u32 m_idxCt;

	GLuint m_vertBuff;
	GLuint m_colBuff;
	GLuint m_normBuff;
	GLuint m_uvBuff;
	GLuint m_idxBuff;

	u32 m_renderConfig;
};
