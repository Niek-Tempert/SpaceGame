#include "renderable.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

template <typename T>
GLint upload_vbuffer(std::vector<T> data) {
	if (data.empty()) {
		return -1;
	}

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(*data.data()) * data.size(), data.data(), GL_STATIC_DRAW);
	return (GLint)buffer;
}

template <typename T>
GLint upload_ibuffer(std::vector<T> data) {
	if (data.empty()) {
		return -1;
	}

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*data.data()) * data.size(), data.data(), GL_STATIC_DRAW);
	return (GLint)buffer;
}

bool has_succeeded(GLuint shader) {
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		fprintf(stderr, "Shader compilation error:\n%s\n", infoLog);
	}

	return success;
}

void link_vbuffer(GLint buffer, GLuint location, GLint size) {
	if (buffer < 0 || location < 0) {
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER, (GLuint)buffer);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, 0);
}

void dispose(RenderObject *object) {
	glDeleteProgram(object->shader);

	if (object->posBuff >= 0) {
		u32 pos_buffer = object->posBuff;
		glDeleteBuffers(1, &pos_buffer);
	}

	if (object->colBuff >= 0) {
		u32 col_buffer = object->colBuff;
		glDeleteBuffers(1, &col_buffer);
	}

	if (object->normBuff >= 0) {
		u32 norm_buffer = object->normBuff;
		glDeleteBuffers(1, &norm_buffer);
	}

	if (object->uvBuff >= 0) {
		u32 uv_buffer = object->uvBuff;
		glDeleteBuffers(1, &uv_buffer);
	}

	if (object->idxBuff >= 0) {
		u32 index_buffer = object->idxBuff;
		glDeleteBuffers(1, &index_buffer);
	}

	glDeleteVertexArrays(1, &object->vao);

	delete object;
}

MRenderable::MRenderable() 
	: m_renderObject() {
	rebuildMesh();
}

MRenderable::~MRenderable() {
	dispose(m_renderObject);
}

void MRenderable::rebuildMesh() {
	if (m_renderObject) {
		dispose(m_renderObject);
	}

	m_renderObject = new RenderObject();
	RenderObject &object = *this->m_renderObject;

	glGenVertexArrays(1, &object.vao);
	glBindVertexArray(object.vao);

	auto verts = getVertices();
	auto cols = getColors();
	auto norms = getNormals();
	auto uvs = getUVs();
	auto indices = getIndices();

	object.vertCt = (i32)verts.size();
	object.idxCt = (i32)indices.size();

	object.posBuff = upload_vbuffer(verts);
	object.colBuff = upload_vbuffer(cols);
	object.normBuff = upload_vbuffer(norms);
	object.uvBuff = upload_vbuffer(uvs);
	object.idxBuff = upload_ibuffer(indices);

	m_renderObject->shader = getShader();
	const GLint pos_loc = glGetAttribLocation(m_renderObject->shader, "vPos");
	const GLint col_loc = glGetAttribLocation(m_renderObject->shader, "vCol");
	const GLint norm_loc = glGetAttribLocation(m_renderObject->shader, "vNorm");
	const GLint uv_loc = glGetAttribLocation(m_renderObject->shader, "vUV");

	link_vbuffer(object.posBuff, pos_loc, sizeof(*verts.data()) / sizeof(f32));
	link_vbuffer(object.colBuff, col_loc, sizeof(*cols.data()) / sizeof(f32));
	link_vbuffer(object.normBuff, norm_loc, sizeof(*norms.data()) / sizeof(f32));
	link_vbuffer(object.uvBuff, uv_loc, sizeof(*uvs.data()) / sizeof(f32));

	glGenTextures(1, &m_renderObject->texBuff);
	glBindTexture(GL_TEXTURE_2D, m_renderObject->texBuff);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	int width, height, nrChannels;
	u8 *data = stbi_load("assets/images/white_wool.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void MRenderable::render(RenderData *data) const {
	if (!m_renderObject) {
		return;
	}

	setGLState();
	beforeRender(data);
	draw();
}

void MRenderable::setGLState() const {
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glLineWidth(1.0f);
}

void MRenderable::beforeRender(RenderData *data) const {
	glm::mat4 model = getTransform();
	glm::mat4 view = data->view;
	glm::mat4 proj = data->proj;
	glm::mat4 mvp = proj * view * model;

	glUseProgram(m_renderObject->shader);
	glUniformMatrix4fv(glGetUniformLocation(m_renderObject->shader, "Model"), 1, GL_FALSE, (const GLfloat*)glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(m_renderObject->shader, "View"), 1, GL_FALSE, (const GLfloat*)glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(m_renderObject->shader, "Proj"), 1, GL_FALSE, (const GLfloat*)glm::value_ptr(proj));
	glUniformMatrix4fv(glGetUniformLocation(m_renderObject->shader, "MVP"), 1, GL_FALSE, (const GLfloat*)glm::value_ptr(mvp));

	glBindTexture(GL_TEXTURE_2D, m_renderObject->texBuff);
	glBindVertexArray(m_renderObject->vao);
}

void MRenderable::draw() const {
	if (m_renderObject->idxCt > 0) {
		glDrawElements(GL_TRIANGLES, m_renderObject->idxCt, GL_UNSIGNED_INT, (void *)0);
		return;
	}
	
	glDrawArrays(GL_TRIANGLES, 0, m_renderObject->vertCt);
}
