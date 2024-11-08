#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include "models/cube.h"
#include "models/cursor.h"

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

#include "rendering/renderable.h"
#include "utils/file.h"
#include "voxel/voxel.h"

struct state {
	double delta_time;
	Player *player;
	Input *input;
	Voxel *voxel;
	Voxel *moon;
	Cursor *cursor;
	std::vector<IRenderable *> renderables;
} state;

static void error_callback(int error, const char *description) {
	fprintf(stderr, "Error: %s\n", description);
}

void generate_objects(GLFWwindow *window) {
	state.player = new Player();
	state.input = Input::init(window);
	state.voxel = new Voxel();
	int length = 25;
	for (int x = -length; x < length; ++x) {
		for (int y = -length; y < length; ++y) {
			for (int z = -length; z < length; ++z) {
				glm::vec3 vec = {(float)x, (float)y, (float)z};
				if (glm::length(vec) > (float)length) {
					continue;
				}
				
				state.voxel->request({ x, y, z }).data = (void *)1;
			}
		}
	}

	
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, -length - 1, 0));
	state.voxel->mesher->transform = model;

	state.voxel->mesher->full_update(state.voxel);
	state.renderables.push_back(state.voxel->mesher);
	
	state.moon = new Voxel();
	int moon_length = 8;
	for (int x = -moon_length; x < moon_length; ++x) {
		for (int y = -moon_length; y < moon_length; ++y) {
			for (int z = -moon_length; z < moon_length; ++z) {
				glm::vec3 vec = {(float)x, (float)y, (float)z};
				if (glm::length(vec) > (float)moon_length) {
					continue;
				}
				
				state.moon->request({ x, y, z }).data = (void *)1;
			}
		}
	}

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, 0, length + moon_length * 2));
	state.moon->mesher->transform = model;
	
	state.moon->mesher->full_update(state.moon);
	state.renderables.push_back(state.moon->mesher);

	for (int i = -1; i < 2; ++i) {
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(i * 2, 0, -4));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1, 0, 0));
		Monkey *monkey = new Monkey();
		monkey->transform = translate * rotate;
		state.renderables.push_back(monkey);
	}

	for (auto renderable : state.renderables) {
		renderable->prepare();
	}

	state.cursor = new Cursor();
	state.cursor->prepare();
	state.renderables.push_back(state.cursor);
}

void render(GLFWwindow *window) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	const float ratio = (float)width / (float)height;

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), -state.player->position);
		
	glm::mat4 rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, -state.player->rotation.x, glm::vec3(1, 0, 0));
	rot = glm::rotate(rot, -state.player->rotation.y, glm::vec3(0, 1, 0));
	rot = glm::rotate(rot, -state.player->rotation.z, glm::vec3(0, 0, 1));

	glm::mat4 v = rot * trans;
	glm::mat4 p = glm::perspective(glm::radians(90.0f), ratio, 0.01f, 100.0f);

	for (auto renderable : state.renderables) {
		renderable->render(v, p);
	}
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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	
	generate_objects(window);

	double last_time = glfwGetTime();
	
	while (!glfwWindowShouldClose(window)) {
		state.player->update(state.input);
		state.delta_time = glfwGetTime() - last_time;

		glm::vec3 position = glm::vec3(state.moon->mesher->transform[3]);
		double t = state.delta_time * 0.05;
		double sin = glm::sin(t);
		double cos = glm::cos(t);
		glm::vec3 rotated_pos = {
			position.x * cos + position.z * sin,
			position.y,
			position.z * cos - position.x * sin
		};
		state.moon->mesher->transform = glm::translate(glm::mat4(1.0f), rotated_pos);
		
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		last_time = glfwGetTime();
		state.input->next();

		render(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}