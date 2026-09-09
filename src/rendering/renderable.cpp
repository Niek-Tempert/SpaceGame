#include "renderable.hpp"

#include <common/helpers.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

static GLenum getRenderMode(u32 config) {
	if ((config & (u32)RenderConfig::Lines) == (u32)RenderConfig::Lines) {
		return GL_LINES;
	}
	
	return GL_TRIANGLES;
}

Renderable::Renderable(const CameraProvider* parent, u32 config)
	: CameraProvider(parent)
	, m_shader()
	, m_vertBuff()
	, m_colBuff()
	, m_normBuff()
	, m_uvBuff()
	, m_idxBuff()
	, m_vao()
	, m_renderConfig(config) {
	setup();
}

Renderable::~Renderable() {
	dispose();
}

void Renderable::render() const {
	glm::mat4 model = getTransform();
	glm::mat4 view = getView();
	glm::mat4 proj = getProj();
	glm::mat4 mvp = proj * view * model;

	setGLState();

	glUseProgram(m_shader);

	glUniformMatrix4fv(glGetUniformLocation(m_shader, "Model"), 1, GL_FALSE, (const GLfloat*)glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "View"), 1, GL_FALSE, (const GLfloat*)glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "Proj"), 1, GL_FALSE, (const GLfloat*)glm::value_ptr(proj));
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "MVP"), 1, GL_FALSE, (const GLfloat*)glm::value_ptr(mvp));

	glBindVertexArray(m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idxBuff);

	if ((m_renderConfig & (u32)RenderConfig::Indexed) == (u32)RenderConfig::Indexed) {
		glDrawElements(getRenderMode(m_renderConfig), m_idxCt, GL_UNSIGNED_INT, (void*)0);
		return;
	}
	glDrawArrays(getRenderMode(m_renderConfig), 0, m_vertCt);
}

void Renderable::remesh() {
	dispose();
	setup();
}

void Renderable::setGLState() const {
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glLineWidth(1.0f);
}

GLuint Renderable::getShader() const {
	return 0;
}

std::vector<glm::vec3> Renderable::getVertices() const {
	return {};
}

std::vector<glm::vec3> Renderable::getColors() const {
	return {};
}

std::vector<glm::vec3> Renderable::getNormals() const {
	return {};
}

std::vector<glm::vec2> Renderable::getUVs() const {
	return {};
}

std::vector<u32> Renderable::getIndices() const {
	return {};
}

glm::mat4 Renderable::getTransform() const {
	return glm::mat4(1.0f);
}

void Renderable::setup() {
	m_vertCt = 0;
	m_idxCt = 0;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	m_shader = getShader();

	GLint vertAttr = glGetAttribLocation(m_shader, "vPos");
	if (vertAttr >= 0) {
		std::vector<glm::vec3> verts = getVertices();
		glGenBuffers(1, &m_vertBuff);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertBuff);
		glBufferData(GL_ARRAY_BUFFER, sizeof(*verts.data()) * verts.size(), verts.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(vertAttr);
		glVertexAttribPointer(vertAttr, 3, GL_FLOAT, GL_FALSE, 0, 0);
		m_vertCt = (u32)verts.size();
	}

	GLint colAttr = glGetAttribLocation(m_shader, "vCol");
	if (colAttr >= 0) {
		std::vector<glm::vec3> cols = getColors();
		glGenBuffers(1, &m_colBuff);
		glBindBuffer(GL_ARRAY_BUFFER, m_colBuff);
		glBufferData(GL_ARRAY_BUFFER, sizeof(*cols.data()) * cols.size(), cols.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(colAttr);
		glVertexAttribPointer(colAttr, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	GLint normAttr = glGetAttribLocation(m_shader, "vNorm");
	if (normAttr >= 0) {
		std::vector<glm::vec3> norms = getNormals();
		glGenBuffers(1, &m_normBuff);
		glBindBuffer(GL_ARRAY_BUFFER, m_normBuff);
		glBufferData(GL_ARRAY_BUFFER, sizeof(*norms.data()) * norms.size(), norms.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(normAttr);
		glVertexAttribPointer(normAttr, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	
	GLint uvAttr = glGetAttribLocation(m_shader, "vUV");
	if (uvAttr >= 0) {
		std::vector<glm::vec2> uvs = getUVs();
		glGenBuffers(1, &m_uvBuff);
		glBindBuffer(GL_ARRAY_BUFFER, m_uvBuff);
		glBufferData(GL_ARRAY_BUFFER, sizeof(*uvs.data()) * uvs.size(), uvs.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(uvAttr);
		glVertexAttribPointer(uvAttr, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	std::vector<u32> indices = getIndices();
	if (indices.size() > 0) {
		glGenBuffers(1, &m_idxBuff);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idxBuff);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*indices.data()) * indices.size(), indices.data(), GL_STATIC_DRAW);
		m_idxCt = (u32)indices.size();
	}
}

void Renderable::dispose() {
	glDeleteProgram(m_shader);
	glDeleteBuffers(1, &m_vertBuff);
	glDeleteBuffers(1, &m_colBuff);
	glDeleteBuffers(1, &m_normBuff);
	glDeleteBuffers(1, &m_uvBuff);
	glDeleteBuffers(1, &m_idxBuff);
	glDeleteVertexArrays(1, &m_vao);

	m_shader = 0;
	m_vertBuff = 0;
	m_colBuff = 0;
	m_normBuff = 0;
	m_uvBuff = 0;
	m_idxBuff = 0;
	m_vao = 0;

	m_vertCt = 0;
	m_idxCt = 0;
}
