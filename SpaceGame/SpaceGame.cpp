#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include "nixelib/src/nixemath.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/Input.hpp"
#include "utils/player.h"

#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <iostream>

#include "models/monkey.h"
#include "utils/file.h"

struct state {
	Player *player;
	Input *input;
} state;

static void error_callback(int error, const char *description) {
	fprintf(stderr, "Error: %s\n", description);
}

int main() {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DEPTH_BITS, GL_TRUE);

	GLFWwindow *window = glfwCreateWindow(1920, 1080, "OpenGL Triangle", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	state.player = new Player();
	state.player->position = { 0, 0, -2 };
	state.input = Input::init(window);

	// glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	const char *vert_shader_str = load_text("shaders/vert/basic.glsl").data();
	const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vert_shader_str, NULL);
	glCompileShader(vertex_shader);

	const char *frag_shader_str = load_text("shaders/frag/basic.glsl").data();
	const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &frag_shader_str, NULL);
	glCompileShader(fragment_shader);

	const GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	const GLint mvp_location = glGetUniformLocation(program, "MVP");
	const GLint vpos_location = glGetAttribLocation(program, "vPos");
	const GLint vcol_location = glGetAttribLocation(program, "vCol");

	GLuint vertex_array;
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);
	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
			sizeof(vertex), (void *)offsetof(vertex, pos));
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
			sizeof(vertex), (void *)offsetof(vertex, col));
	
	while (!glfwWindowShouldClose(window)) {
		/* Handle input */
		state.player->update(state.input);
		
		std::cout << "{" << state.player->position.x << ", " << state.player->position.y << ", " << state.player->position.z << "}, {" << glm::degrees(state.player->rotation.x) << ", " << glm::degrees(state.player->rotation.y) << "}" << std::endl;

		/* Cleanup buffer */
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		const float ratio = width / (float)height;
		
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		state.input->next();

		/* Setup transforms */
		glm::mat4 trans = glm::translate(glm::mat4(1.0f), state.player->position);
		glm::mat4 rot = glm::rotate(glm::mat4(1.0f), -state.player->rotation.x, glm::vec3(1, 0, 0));
		rot = glm::rotate(rot, -state.player->rotation.y, glm::vec3(0, 1, 0));

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
		glm::mat4 view = rot * trans;
		glm::mat4 proj = glm::perspective(glm::radians(90.0f), ratio, 0.01f, 100.0f);
		glm::mat4 mvp = proj * view * model;
		
		/* Render */
		glUseProgram(program);
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)glm::value_ptr(mvp));
		glBindVertexArray(vertex_array);
		glDrawArrays(GL_TRIANGLES, 0, VERT_COUNT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}