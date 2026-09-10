#include "glwindow.hpp"

#include <glad/glad.h>
#include <iostream>

static void error_callback(i32 error, const char* description) {
	std::cerr << "Error: " << description << "\n";
}

GLWindow::GLWindow()
	: m_window()
    , m_focussed(false)
    , m_fullscreen(false)
    , m_input() {
    glfwSetErrorCallback(error_callback);

	if (!glfwInit()) return;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DEPTH_BITS, GL_TRUE);

	m_window = glfwCreateWindow(640, 480, "SpaceGame", NULL, NULL);

	if (!m_window) { 
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	m_input.init(m_window);
}

GLWindow::~GLWindow() {
    glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool GLWindow::next() {
    if (glfwWindowShouldClose(m_window)) return false;
	m_input.next();
	glfwSwapBuffers(m_window);
	glfwPollEvents();

    if (m_input.getKey(GLFW_KEY_F11)) {
		toggleFullscreen();
	}

	if (!m_focussed && m_input.getMouse(GLFW_MOUSE_BUTTON_1)) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		m_focussed = true;
		m_input.setEnabled(m_focussed);
	}

	if (m_focussed && m_input.getKey(GLFW_KEY_ESCAPE)) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_focussed = false;
		m_input.setEnabled(m_focussed);
	}

	glm::ivec2 size = getResolution();
	glViewport(0, 0, size.x, size.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return true;
}

const Input *GLWindow::getInput() const {
	return &m_input;
}

void GLWindow::toggleFullscreen() {
	GLFWmonitor *monitor = m_fullscreen ? NULL : glfwGetPrimaryMonitor();
	glfwSetWindowMonitor(m_window, monitor, 0, 0, 640, 480, GLFW_DONT_CARE);
	m_fullscreen = !m_fullscreen;
}

glm::ivec2 GLWindow::getResolution() const {
    i32 width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
	return { width, height };
}

bool GLWindow::isFocussed() const {
	return m_focussed;
}

GLFWwindow *GLWindow::getGLFW() const {
	return m_window;
}
