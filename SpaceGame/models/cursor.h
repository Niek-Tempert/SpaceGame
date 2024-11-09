#pragma once

#include "rendering/renderable.h"

#include <glad/gl.h>

#include <glm/gtc/type_ptr.hpp>

class Cursor : public IRenderable {
public:
	void prepare() override {
		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"uniform mat4 trans;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = trans * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";
		
		const char *fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(1.0f);\n"
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
		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);
		// check for linking errors

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		vertices = {
			-16, 0, 0,
			16, 0, 0,
			0, -16, 0,
			0, 16, 0
	   };
        
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertices.size() * sizeof(*vertices.data())), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	void render(draw_call_data* data) const override {
		glUseProgram(program);
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3((float)data->resolution.x / 2.0f, (float)data->resolution.y / 2.0f, 0.0f));
		trans = glm::ortho(0.0f, (f32)data->resolution.x, 0.0f, (f32)data->resolution.y, 1.0f, -1.0f) * trans;

		GLint trans_loc = glGetUniformLocation(program, "trans");
		glUniformMatrix4fv(trans_loc, 1, GL_FALSE, (const GLfloat *)glm::value_ptr(trans));

		glLineWidth(4.0f);
		glBindVertexArray(vao);
		
		glDrawArrays(GL_LINES, 0, (u32)vertices.size());
	}

private:
	i32 program = -1;
	u32 vao = 0;
	std::vector<f32> vertices;
};
