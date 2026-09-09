#include "engine.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

Engine::Engine()
	: InputProvider(&m_window)
	, CanvasProvider(&m_window)
	, TimeProvider(&m_time, &m_deltaTime)
	, m_window()
	, m_scene(this) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_window.getGLFW(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

Engine::~Engine() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Engine::exec() {
	while (m_window.next()) {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		f32 now = glfwGetTime();
		m_deltaTime = now - m_time;
		m_time = now;

		m_scene.update();
		m_scene.render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
