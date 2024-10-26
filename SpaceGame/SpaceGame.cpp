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

static constexpr float walk_speed = 0.1f;
static constexpr float look_speed = 0.01f;

struct state {
	Player *player;
	Input *input;
} state;

static const char *vertex_shader_text =
		"#version 330\n"
		"uniform mat4 MVP;\n"
		"in vec3 vCol;\n"
		"in vec3 vPos;\n"
		"out vec3 color;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = MVP * vec4(vPos, 1.0);\n"
		"    color = vCol;\n"
		"}\n";

static const char *fragment_shader_text =
		"#version 330\n"
		"in vec3 color;\n"
		"out vec4 fragment;\n"
		"void main()\n"
		"{\n"
		"    fragment = vec4(color, 1.0);\n"
		"}\n";

static void error_callback(int error, const char *description) {
	fprintf(stderr, "Error: %s\n", description);
}

void update() { // TODO: Move to Player.cs
	
	Input& input = *state.input;
	Player& player = *state.player;
	
	glm::vec2 delta = { input.get_cursor_delta().x, input.get_cursor_delta().y };
	
	player.rotation.x = glm::clamp(player.rotation.x + delta.y * look_speed, -1.f, 1.f);
	player.rotation.y = nixemath::wrap(player.rotation.y + delta.x * look_speed, -glm::pi<f32>(), glm::pi<f32>());

	glm::vec3 dir = { 0, 0, 0};
	if (input.is_key_down(GLFW_KEY_W)) {
		dir += glm::vec3(glm::sin(player.rotation.y), 0, glm::cos(player.rotation.y));
	}

	if (input.is_key_down(GLFW_KEY_A)) {
		dir += glm::vec3(glm::cos(player.rotation.y), 0, -glm::sin(player.rotation.y));
	}
	
	if (input.is_key_down(GLFW_KEY_S)) {
		dir += glm::vec3(-glm::sin(player.rotation.y), 0, -glm::cos(player.rotation.y));
	}

	if (input.is_key_down(GLFW_KEY_D)) {
		dir += glm::vec3(-glm::cos(player.rotation.y), 0, glm::sin(player.rotation.y));
	}

	if (glm::length(dir) > 0) {
		player.position += glm::normalize(dir) * walk_speed;
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

	state.player = new Player();
	state.player->position = { 0, 0, 2 };
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

	const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);

	const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
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
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		const float ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		update();

		std::cout << "{" << state.player->position.x << ", " << state.player->position.y << ", " << state.player->position.z << "}, {" << glm::degrees(state.player->rotation.x) << ", " << glm::degrees(state.player->rotation.y) << "}" << std::endl;

		glm::mat4 trans = glm::translate(glm::mat4(1.0f), state.player->position);
		glm::mat4 rot = glm::rotate(glm::mat4(1.0f), -state.player->rotation.x, glm::vec3(1, 0, 0));
		rot = glm::rotate(rot, -state.player->rotation.y, glm::vec3(0, 1, 0));

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
		glm::mat4 view = rot * trans;
		glm::mat4 proj = glm::perspective(glm::radians(90.0f), ratio, 0.01f, 100.0f);
		glm::mat4 mvp = proj * view * model;
		
		state.input->next();
		
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