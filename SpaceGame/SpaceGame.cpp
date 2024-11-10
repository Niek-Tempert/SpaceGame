#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include "models/cube.h"
#include "models/cursor.h"

#include <GLFW/glfw3.h>

#include "models/monkey.h"
#include "models/skybox.h"

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
	Player *player;
	Input *input;
	Voxel *voxel;
	Voxel *moon;
	std::vector<IRenderable *> render_queue;
} state;

static void error_callback(int error, const char *description) {
	fprintf(stderr, "Error: %s\n", description);
}

void build_voxel(Voxel* voxel, int length, glm::vec3 position) {
	for (int x = -length; x < length; ++x) {
		for (int y = -length; y < length; ++y) {
			for (int z = -length; z < length; ++z) {
				glm::vec3 vec = {(float)x, (float)y, (float)z};
				if (glm::length(vec) > (float)length) {
					continue;
				}
				
				voxel->request({ x, y, z }).data = (void *)1;
			}
		}
	}
	
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	voxel->mesher->transform = model;
	voxel->mesher->full_update(voxel);
}

void build_render_queue() {
	state.render_queue.push_back(new Skybox());

	state.voxel = new Voxel();
	state.moon = new Voxel();
	
	build_voxel(state.voxel, 16, { 0, -17, 0 });
	build_voxel(state.moon, 8, { 0, 0, 32 });

	state.render_queue.push_back(state.voxel->mesher);
	state.render_queue.push_back(state.moon->mesher);

	state.render_queue.push_back(new Cursor());
	
	for (auto renderable : state.render_queue) {
		renderable->prepare();
	}
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

	glm::mat4 view = rot * trans;
	glm::mat4 proj = glm::perspective(glm::radians(90.0f), ratio, 0.01f, 500.0f);

	draw_call_data data = {
		view,
		proj,
		{ (u32)width, (u32)height }
	};
	
	for (auto renderable : state.render_queue) {
		renderable->render(&data);
	}
}

void on_update(double delta_time) {
	glm::vec3 position = glm::vec3(state.moon->mesher->transform[3]);
	double t = delta_time * 0.05;
	double sin = glm::sin(t);
	double cos = glm::cos(t);
	glm::vec3 rotated_pos = {
		position.x * cos + position.z * sin,
		position.y,
		position.z * cos - position.x * sin
	};
	state.moon->mesher->transform = glm::translate(glm::mat4(1.0f), rotated_pos);
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

	GLFWwindow *window = glfwCreateWindow(1920, 1080, "SpaceGame", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);

	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);

	build_render_queue();

	state.player = new Player();
	state.input = Input::init(window);

	double last_time = glfwGetTime();
	
	while (!glfwWindowShouldClose(window)) {
		state.player->update(state.input);

		double delta_time = glfwGetTime() - last_time;
		on_update(delta_time);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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