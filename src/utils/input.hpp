#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <common/types.h>

#define KEY_COUNT (GLFW_KEY_LAST + 1)
#define MOUSE_COUNT (GLFW_MOUSE_BUTTON_LAST + 1)

class Input {
public:
	void init(GLFWwindow* window) {
		glfwSetWindowUserPointer(window, this);
		glfwSetCursorPosCallback(window, _cursor_callback);
		glfwSetMouseButtonCallback(window, _mouse_callback);
		glfwSetKeyCallback(window, _keyboard_callback);

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		m_cursor = m_last_cursor = { xpos, ypos };
	}

	void next() {
		/* Reset mouse flags */
		m_mouse_press_flags = 0;
		m_mouse_release_flags = 0;

		/* Reset keys */
		for (u8 &key : m_keys) {
			key &= 1;
		}
		
		m_last_cursor = m_cursor;
	}
	
	glm::vec2 get_cursor() const {
		return m_cursor;
	}

	glm::vec2 get_cursor_delta() const {
		return m_cursor - m_last_cursor;
	}

	bool is_key_down(int key) const {
		u8 flag = 1 << 0;
		return (m_keys[key] & flag) == flag;
	}

	bool is_key_press(int key) const {
		u8 flag = 1 << 1;
		return (m_keys[key] & flag) == flag;
	}

	bool is_key_release(int key) const {
		u8 flag = 1 << 2;
		return (m_keys[key] & flag) == flag;
	}

	bool is_mouse_press(int button) const {
		u8 flag = 1 << button;
		return (m_mouse_press_flags & flag) == flag;
	}

	bool is_mouse_release(int button) const {
		u8 flag = 1 << button;
		return (m_mouse_release_flags & flag) == flag;
	}

	bool is_mouse_down(int button) const {
		u8 flag = 1 << button;
		return (m_mouse_down_flags & flag) == flag;
	}

private:
	glm::vec2 m_cursor;
	glm::vec2 m_last_cursor;
	u8 m_mouse_down_flags = 0;
	u8 m_mouse_press_flags = 0;
	u8 m_mouse_release_flags = 0;
	u8 m_keys[KEY_COUNT] = {};
	
	static void _cursor_callback(GLFWwindow* window, double xpos, double ypos) {
		Input *input = (Input*)glfwGetWindowUserPointer(window);
		
		input->m_cursor = { xpos, ypos };
	}

	static void _mouse_callback(GLFWwindow* window, int button, int action, int mods) {
		Input *input = (Input*)glfwGetWindowUserPointer(window);

		u8 flag;
		switch (action) {
			case GLFW_PRESS:
				flag = 1 << button;

				input->m_mouse_down_flags |= flag;
				input->m_mouse_press_flags |= flag;
			break;

			case GLFW_RELEASE:
				flag = 1 << button;

				input->m_mouse_down_flags &= ~flag;
				input->m_mouse_release_flags |= flag;
			break;
		}
	}
	
	static void _keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Input *input = (Input*)glfwGetWindowUserPointer(window);
		
		switch (action) {
			case GLFW_PRESS:
				input->m_keys[key] |= 1 << 0 | ((input->m_keys[key] & 1) ^ 1) << 1;
			break;

			case GLFW_RELEASE:
				input->m_keys[key] &= ~1;
				input->m_keys[key] |= 1 << 2;
			break;
		}
	}
};

#undef KEY_COUNT
#undef MOUSE_COUNT
