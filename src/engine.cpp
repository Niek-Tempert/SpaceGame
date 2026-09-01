#include "engine.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Engine::Engine()
	: m_window()
	, m_scene() {
	m_scene.init();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_window.getGLFW(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

Engine::~Engine() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Engine::exec() {
	while (m_window.update()) {
		f32 time = m_window.getTime();
		m_scene.m_deltaTime = time - m_scene.m_time;
		m_scene.m_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiIO& io = ImGui::GetIO();
		if (m_window.isFocussed()) {
			io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
		} else {
			io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
		}

		if (m_window.isFocussed()) {
			m_scene.update(m_window.getInput());
		}

		glm::ivec2 size = m_window.getSize();
		glViewport(0, 0, size.x, size.y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		const f32 ratio = (f32)size.x / (f32)size.y;
		glm::mat4 proj = glm::mat4(1.0f); 
		if (!glm::isnan(ratio) && !glm::isinf(ratio)) { 
			proj = glm::perspective(glm::radians(90.0f), ratio, 0.01f, 500.0f);
		}

		for (IRenderable* renderable : m_scene.getRenderables()) {
			RenderData data;
			data.view = m_scene.getView();
			data.proj = proj;
			data.resolution = { (u32)size.x, (u32)size.y };
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
	}
}
