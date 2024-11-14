#pragma once

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include "models/cube.h"
#include "models/cube_lines.h"
#include "models/cursor.h"

#include <GLFW/glfw3.h>

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

struct Program {
	GLFWwindow *window;
	Player *player;
	Input *input;

	double time;
	double delta_time;

	Voxel *moon;
	std::vector<Voxel *> voxels;

	CubeLines *cursor3d;
	std::vector<IRenderable *> render_queue;
};

static void error_callback(int error, const char *description) {
	fprintf(stderr, "Error: %s\n", description);
}

void build_voxel(Voxel *voxel, int length, glm::vec3 position) {
	for (int x = -length; x < length; ++x) {
		for (int y = -length; y < length; ++y) {
			for (int z = -length; z < length; ++z) {
				glm::vec3 vec = { (float)x, (float)y, (float)z };
				if (glm::length(vec) > (float)length) {
					continue;
				}

				voxel->set({ x, y, z }, { (ICell *)1, NULL });
			}
		}
	}

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	voxel->transform = model;
}

void build_render_queue(Program *program) {
	program->render_queue.push_back(new Skybox());

	Voxel *voxel = new Voxel();
	program->moon = new Voxel();

	build_voxel(voxel, 16, { 0, -17, 0 });
	build_voxel(program->moon, 8, { 0, 0, 32 });

	program->voxels.push_back(voxel);
	program->voxels.push_back(program->moon);

	program->render_queue.push_back(voxel);
	program->render_queue.push_back(program->moon);

	program->render_queue.push_back(program->cursor3d = new CubeLines());

	program->render_queue.push_back(new Cursor());

	for (auto renderable : program->render_queue) {
		renderable->prepare();
	}
}

void render(const Program *program) {
	int width, height;
	glfwGetFramebufferSize(program->window, &width, &height);
	const float ratio = (float)width / (float)height;

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), -program->player->position);

	glm::mat4 rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, -program->player->rotation.x, glm::vec3(1, 0, 0));
	rot = glm::rotate(rot, -program->player->rotation.y, glm::vec3(0, 1, 0));
	rot = glm::rotate(rot, -program->player->rotation.z, glm::vec3(0, 0, 1));

	glm::mat4 view = rot * trans;
	glm::mat4 proj = glm::perspective(glm::radians(90.0f), ratio, 0.01f, 500.0f);

	DrawCallData data = {
		view,
		proj,
		{ (u32)width, (u32)height }
	};

	for (auto renderable : program->render_queue) {
		renderable->render(&data);
	}
}

void on_update(const Program *program) {
	glm::vec3 position = glm::vec3(program->moon->transform[3]);
	const double t = program->delta_time * 0.05;
	const double sin = glm::sin(t);
	const double cos = glm::cos(t);
	glm::vec3 rotated_pos = {
		position.x * cos + position.z * sin,
		position.y,
		position.z * cos - position.x * sin
	};

	program->moon->transform = glm::translate(glm::mat4(1.0f), rotated_pos);

	glm::mat4 rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, program->player->rotation.z, glm::vec3(0, 0, 1));
	rot = glm::rotate(rot, program->player->rotation.y, glm::vec3(0, 1, 0));
	rot = glm::rotate(rot, program->player->rotation.x, glm::vec3(1, 0, 0));

	glm::vec3 direction = rot * glm::vec4(0, 0, -1, 1);

	f32 dist = 4.0f;
	RaycastResult result;
	Voxel *hit_voxel = nullptr;
	for (auto voxel : program->voxels) {
		RaycastResult voxel_result = voxel->raycast(
				{ program->player->position.x, program->player->position.y, program->player->position.z },
				{ direction.x, direction.y, direction.z },
				dist
				);

		if (voxel_result.hit) {
			hit_voxel = voxel;
			dist = result.distance;
			result = voxel_result;
		}
	}

	program->cursor3d->visible = result.hit;
	if (result.hit) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(result.id.x, result.id.y, result.id.z));
		model = hit_voxel->transform * model;
		program->cursor3d->transform = model;

		if (program->input->is_mouse_press(GLFW_MOUSE_BUTTON_1) && result.hit) {
			hit_voxel->set(result.id, { NULL, NULL });
			hit_voxel->update(result.id);
		}

		if (program->input->is_mouse_press(GLFW_MOUSE_BUTTON_2)) {
			hit_voxel->set(result.id + result.normal, { (ICell *)1, NULL });
			hit_voxel->update(result.id + result.normal);
		}
	}
}

void start(Program **program) {
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

	*program = new Program();
	build_render_queue(*program);

	(*program)->window = window;
	(*program)->player = new Player();
	(*program)->input = Input::init(window);
}

void update(Program *program) {
	while (!glfwWindowShouldClose(program->window)) {
		program->player->update(program->input);

		double time = glfwGetTime();
		program->delta_time = program->time - time;
		program->time = time;

		on_update(program);

		int width, height;
		glfwGetFramebufferSize(program->window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		program->input->next();

		render(program);

		glfwSwapBuffers(program->window);
		glfwPollEvents();
	}
}

void cleanup(const Program *program) {
	glfwDestroyWindow(program->window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}