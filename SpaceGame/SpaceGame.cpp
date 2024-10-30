#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include "models/cube.h"

#include <GLFW/glfw3.h>

#include "models/monkey.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/input.hpp"
#include "utils/player.h"

#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <iostream>

#include "rendering/renderable.h"
#include "utils/file.h"
#include "voxel/voxel.h"

struct state {
	Player *player;
	Input *input;
	Voxel *voxel;
	std::vector<IRenderable *> renderables;
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
	state.voxel = new Voxel();

	for (int i = -1; i < 2; ++i) {
		glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1, 0, 0));
		transform = glm::translate(transform, glm::vec3(i * 2, 0, 0));
		Monkey *monkey = new Monkey();
		monkey->transform = transform;
		state.renderables.push_back(monkey);
		
		transform = glm::translate(transform, glm::vec3(0, -8, 0));
		Cube *cube = new Cube();
		cube->transform = transform;
		state.renderables.push_back(cube);
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	for (auto renderable : state.renderables) {
		renderable->prepare();
	}

	while (!glfwWindowShouldClose(window)) {
		/* Handle input */
		state.player->update(state.input);

		std::cout << "{" << state.player->position.x << ", " << state.player->position.y << ", " << state.player->position.z << "}, {" << glm::degrees(state.player->rotation.x) << ", " << glm::degrees(state.player->rotation.y) << ", " << glm::degrees(state.player->rotation.z) << "}" << std::endl;

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

		glm::mat4 view = rot * trans;
		glm::mat4 proj = glm::perspective(glm::radians(90.0f), ratio, 0.01f, 100.0f);

		for (auto renderable : state.renderables) {
			renderable->render(view, proj);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}