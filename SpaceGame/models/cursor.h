#pragma once

#include "rendering/renderable.h"

#include <glad/gl.h>

#include <glm/gtc/type_ptr.hpp>

class Cursor : public IRenderable {
public:
	void prepare() override {
		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"uniform mat4 P;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = P * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";
		const char *fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
			"}\n\0";

		// vertex shader
		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		// check for shader compile errors

		// fragment shader
		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		// check for shader compile errors

		// link shaders
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// check for linking errors

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		vertices = {
			-0.025, 0, -1,
			0.025, 0, -1,
			0, -0.025, -1,
			0, 0.025, -1
	   };
        
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	void render(glm::mat4 v, glm::mat4 p) const override {
		glUseProgram(shaderProgram);
		auto p_loc = glGetUniformLocation(shaderProgram, "P");
		glUniformMatrix4fv(p_loc, 1, GL_FALSE, (const GLfloat *)glm::value_ptr(p));

		glLineWidth(4.0f);
		glBindVertexArray(VAO);
		
		glDrawArrays(GL_LINES, 0, (u32)vertices.size());
	}

private:
	i32 shaderProgram;
	u32 VAO;
	std::vector<f32> vertices;
};
