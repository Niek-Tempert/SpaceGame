#include "engine.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Engine::Engine() 
	: m_window()
	, m_scene(m_window, m_window) {
}

void Engine::exec() {
	while (m_window.update()) {
		m_scene.update();

		glm::ivec2 size = m_window.getSize();
		glViewport(0, 0, size.x, size.y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_scene.render();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
