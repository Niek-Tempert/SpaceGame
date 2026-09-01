#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <common/types.h>

#define KEY_COUNT (GLFW_KEY_LAST + 1)

class Input {
public:
	void init(GLFWwindow* window);
	void next();
	glm::vec2 getCursor() const;
	glm::vec2 getCursorDelta() const;
	bool getKey(i32 key) const;
	bool getKeyUp(i32 key) const;
	bool getKeyDown(i32 key) const;
	bool getMouse(i32 button) const;
	bool getMouseUp(i32 button) const;
	bool getMouseDown(i32 button) const;

private:
	glm::vec2 m_cursor;
	glm::vec2 m_lastCursor;
	u8 m_mouseDownFlags = 0;
	u8 m_mousePressFlags = 0;
	u8 m_mouseReleaseFlags = 0;
	u8 m_keys[KEY_COUNT] = {};

	static void keyboardCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods);
	static void mouseCallback(GLFWwindow* window, i32 button, i32 action, i32 mods);
	static void cursorCallback(GLFWwindow* window, f64 xpos, f64 ypos);
};
