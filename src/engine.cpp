#include "engine.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static void error_callback(int error, const char *description) {
	fprintf(stderr, "Error: %s\n", description);
}

Engine::Engine() {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) return;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DEPTH_BITS, GL_TRUE);

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);

	m_window = glfwCreateWindow(1920, 1080, "SpaceGame", NULL, NULL);
	glfwSetWindowMonitor(m_window, NULL, mode->width / 4, mode->height / 4, mode->width / 2, mode->height / 2, GLFW_DONT_CARE);

	if (!m_window) { 
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);
	gladLoadGL();
	glfwSwapInterval(1);

	m_input.init(m_window);
	m_scene.init();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

Engine::~Engine() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Engine::exec() {
	while (!glfwWindowShouldClose(m_window)) {
		f32 time = glfwGetTime();
		m_scene.m_deltaTime = time - m_scene.m_time;
		m_scene.m_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiIO& io = ImGui::GetIO();
		if (m_focussed) {
			io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
		} else {
			io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
		}

		if (m_focussed) {
			m_scene.update(&m_input);
		}

		if (m_input.is_key_press(GLFW_KEY_F11)) {
			if (m_fullscreen) {
				GLFWmonitor *monitor = glfwGetPrimaryMonitor();
				const GLFWvidmode *mode = glfwGetVideoMode(monitor);

				glfwSetWindowMonitor(m_window, NULL, mode->width / 4, mode->height / 4, mode->width / 2, mode->height / 2, GLFW_DONT_CARE);
				m_fullscreen = false;
			} else {
				GLFWmonitor *monitor = glfwGetPrimaryMonitor();
				const GLFWvidmode *mode = glfwGetVideoMode(monitor);

				glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
				m_fullscreen = true;
			}
		}

		if (m_input.is_key_press(GLFW_KEY_ESCAPE)) {
			if (m_focussed) {
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				m_focussed = false;
			}
		}

		if (m_input.is_mouse_press(GLFW_MOUSE_BUTTON_1)) {
			if (!m_focussed && !ImGui::GetIO().WantCaptureMouse) {
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				m_focussed = true;
			}
		}

		i32 width, height;
		glfwGetFramebufferSize(m_window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_input.next();

		const f32 ratio = (f32)width / (f32)height;
		glm::mat4 proj = glm::mat4(1.0f); 
		if (!glm::isnan(ratio) && !glm::isinf(ratio)) { 
			proj = glm::perspective(glm::radians(90.0f), ratio, 0.01f, 500.0f);
		}

		for (IRenderable* renderable : m_scene.getRenderables()) {
			RenderData data;
			data.view = m_scene.getView();
			data.proj = proj;
			data.resolution = { (u32)width, (u32)height };
			renderable->render(&data);
		}
		
		ImGui::Begin("Settings");
		ImGui::DragFloat("Speed", &m_scene.m_speed, 0.01f);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}
