#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include "nixelib/src/nixemath.h"

#include <GLFW/glfw3.h>

#include "third_party/linmath.h"
#include "utils/player.h"

#include <cstdlib>
#include <cstddef>
#include <cstdio>

static Player player;

struct Vertex {
	vec3 pos;
	vec3 col;
};

static const Vertex vertices[3] =
{
	{ { -0.6f, -0.4f, -1.f }, { 1.f, 0.f, 0.f } },
	{ { 0.6f, -0.4f, -1.f }, { 0.f, 1.f, 0.f } },
	{ { 0.f, 0.6f, -1.f }, { 0.f, 0.f, 1.f } }
};

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

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
	}

	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;
		}
		
	}
	
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {
			case GLFW_KEY_W:
				player.position[2] += 0.1f;
				break;

			case GLFW_KEY_A:
				player.position[0] -= 0.1f;
				break;
			
			case GLFW_KEY_S:
				player.position[2] -= 0.1f;
				break;

			case GLFW_KEY_D:
				player.position[0] += 0.1f;
				break;
		}
	}
}

float last_x, last_y;

static void cursor_callback(GLFWwindow *window, double xpos, double ypos) {
	xpos *= .01f;
	ypos *= .01f;
	player.rotation[0] = nixemath::clamp(player.rotation[0] + last_y - (float)ypos, -1.f, 1.f);
	player.rotation[1] += last_x - (float)xpos;
	last_x = xpos;
	last_y = ypos;
}

int main() {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);

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
			sizeof(Vertex), (void *)offsetof(Vertex, pos));
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void *)offsetof(Vertex, col));

	while (!glfwWindowShouldClose(window)) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		const float ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		mat4x4 m, p, t, r, mvp;
		mat4x4_identity(m); // Initialize the model matrix to identity
		mat4x4_translate(t, player.position[0], player.position[1], player.position[2]); // Apply translation
		mat4x4_rotate_X(r, m, player.rotation[0]); // Apply rotation around the X-axis
		mat4x4_rotate_Y(r, r, player.rotation[1]); // Apply rotation around the Y-axis
		mat4x4_mul(m, r, t); // Combine translation and rotation into the model matrix
		mat4x4_perspective(p, 60.f, ratio, 0.001f, 100.f); // Create the projection matrix
		mat4x4_mul(mvp, p, m); // Combine projection and model matrices to get the final MVP matrix

		glUseProgram(program);
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)&mvp);
		glBindVertexArray(vertex_array);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}