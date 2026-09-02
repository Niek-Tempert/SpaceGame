#include "glwindow.hpp"

#include <glad/glad.h>
#include <cstdio>
#include <imgui.h>

static void error_callback(int error, const char *description) {
	fprintf(stderr, "Error: %s\n", description);
}

GLWindow::GLWindow()
    : TimeProvider(&m_time, &m_deltaTime)
	, m_window()
    , m_focussed(false)
    , m_fullscreen(false)
    , m_input() 
	, m_time()
	, m_deltaTime() {
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
	gladLoadGL();
	glfwSwapInterval(1);

	m_input.init(m_window);
}

GLWindow::~GLWindow() {
    glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool GLWindow::update() {
    if (glfwWindowShouldClose(m_window)) return false;

	m_input.next();
	glfwSwapBuffers(m_window);
	glfwPollEvents();

	f32 now = glfwGetTime();
	m_deltaTime = now - m_time;
	m_time = now;

    if (m_input.getKey(GLFW_KEY_F11)) {
		toggleFullscreen();
	}

	if (!m_focussed && !ImGui::GetIO().WantCaptureMouse && m_input.getMouse(GLFW_MOUSE_BUTTON_1)) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		m_focussed = true;
	}

	if (m_focussed && m_input.getKey(GLFW_KEY_ESCAPE)) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_focussed = false;
	}

	return true;
}

const Input *GLWindow::getInput() const {
	return &m_input;
}

GLFWwindow *GLWindow::getGLFW() const {
	return m_window;
}

f32 GLWindow::getTime() {
	return m_time;
}

f32 GLWindow::getDeltaTime() {
	return m_deltaTime;
}

void GLWindow::toggleFullscreen() {
	if (m_fullscreen) {
		glfwSetWindowMonitor(m_window, NULL, 0, 0, 640, 480, GLFW_DONT_CARE);
		m_fullscreen = !m_fullscreen;
		return;
	}

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	glfwSetWindowMonitor(m_window, monitor, 0, 0, 640, 480, GLFW_DONT_CARE);
	m_fullscreen = !m_fullscreen;
}

glm::ivec2 GLWindow::getSize() const {
    i32 width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
	return { width, height };
}

bool GLWindow::isFocussed() const {
	return m_focussed;
}
