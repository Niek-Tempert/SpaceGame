#include "engine.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Engine::Engine()
	: InputProvider(&m_window)
	, CanvasProvider(&m_window)
	, TimeProvider(&m_time, &m_deltaTime)
	, m_window()
	, m_scene(this) {
}

void Engine::exec() {
	while (m_window.update()) {
		f32 now = glfwGetTime();
		m_deltaTime = now - m_time;
		m_time = now;

		m_scene.update();

		glm::ivec2 size = m_window.getSize();
		glViewport(0, 0, size.x, size.y);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_scene.render();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
