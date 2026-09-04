#include "renderable.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <common/helpers.h>
#include <engine/scene.hpp>
#include "renderable.hpp"

Renderable::Renderable(const Scene* parent)
	: CameraProvider(parent)
	, m_vertBuff()
	, m_colBuff()
	, m_normBuff()
	, m_uvBuff()
	, m_idxBuff()
	, m_renderType(GL_TRIANGLES) {
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
	
	i32 width, height, nrChannels;
	u8* data = stbi_load(IMAGE_PATH "white_wool.png", &width, &height, &nrChannels, 0);
	if (data) {
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
		return;
	}

	std::cout << "Failed to load texture" << std::endl;
	stbi_image_free(data);
}

Renderable::~Renderable() {
	glDeleteProgram(m_shader);
	glDeleteTextures(1, &m_texture);
	glDeleteBuffers(1, &m_vertBuff);
	glDeleteBuffers(1, &m_colBuff);
	glDeleteBuffers(1, &m_normBuff);
	glDeleteBuffers(1, &m_uvBuff);
	glDeleteBuffers(1, &m_idxBuff);
	glDeleteVertexArrays(1, &m_vao);
}

void Renderable::render() const {
	glm::mat4 model = getTransform();
	glm::mat4 view = getView();
	glm::mat4 proj = getProj();
	glm::mat4 mvp = proj * view * model;

	// glEnable(GL_DEPTH_TEST);
	// glDepthMask(GL_TRUE);
	// glEnable(GL_CULL_FACE);
	// glDepthFunc(GL_LEQUAL);
	// glLineWidth(1.0f);

	glUseProgram(m_shader);

	glUniformMatrix4fv(glGetUniformLocation(m_shader, "Model"), 1, GL_FALSE, (const GLfloat*)glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "View"), 1, GL_FALSE, (const GLfloat*)glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "Proj"), 1, GL_FALSE, (const GLfloat*)glm::value_ptr(proj));
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "MVP"), 1, GL_FALSE, (const GLfloat*)glm::value_ptr(mvp));

	glBindVertexArray(m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_idxBuff);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	if (m_idxCt > 0) {
		glDrawElements(m_renderType, m_idxCt, GL_UNSIGNED_INT, (void *)0);
		return;
	}
	glDrawArrays(m_renderType, 0, m_vertCt);
}

void Renderable::setRenderType(GLenum type) {
	m_renderType = type;
}
