#pragma once

#include <GLFW/glfw3.h>
#include <common/types.h>
#include <glm/vec2.hpp>

class GLWindow;

class InputProvider {
public:
	InputProvider(const GLWindow* window);
	InputProvider(const InputProvider* provider);

protected:
    glm::vec2 getCursor() const;
	glm::vec2 getCursorDelta() const;
	bool getKey(i32 key) const;
	bool getKeyUp(i32 key) const;
	bool getKeyDown(i32 key) const;
	bool getMouse(i32 button) const;
	bool getMouseUp(i32 button) const;
	bool getMouseDown(i32 button) const;

private:
    const GLWindow* m_window;
};
