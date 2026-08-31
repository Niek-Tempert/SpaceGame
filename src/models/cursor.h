#pragma once

#include "rendering/renderable.h"
#include "rendering/line_renderable.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

class Cursor : public MLineRenderable {
public:
	void setGLState() const override {
		MRenderable::setGLState();
		glLineWidth(4.0f);
	}

	std::vector<glm::vec3> getVertices() const override {
		return {
			{ -16.0f, 0.0f, 0.0f },
			{ 16.0f, 0.0f, 0.0f },
			{ 0.0f, -16.0f, 0.0f },
			{ 0.0f, 16.0f, 0.0f }
		};
	}

	GLuint getShader() const override {
		GLuint shader = 0;
		if (shaderLoadVF(&shader, SHADER_PATH "cursor.vert", SHADER_PATH "cursor.frag")) throw;
		return shader;
	}

	void beforeRender(RenderData *data) const override {
		glUseProgram(m_renderObject->shader);

		glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((float)data->resolution.x / 2.0f, (float)data->resolution.y / 2.0f, 0.0f));
		glm::mat4 ortho = glm::ortho(0.0f, (f32)data->resolution.x, 0.0f, (f32)data->resolution.y, 1.0f, -1.0f);
		glm::mat4 view = ortho * trans;

		glUniformMatrix4fv(glGetUniformLocation(m_renderObject->shader, "view"), 1, GL_FALSE, (const GLfloat*)glm::value_ptr(view));
		glBindVertexArray(m_renderObject->vao);
	}
};
