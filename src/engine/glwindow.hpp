#pragma once

#include "input.hpp"

class GLFWwindow;

class GLWindow {
public:
    GLWindow();
    ~GLWindow();
    bool update();
    const Input* getInput() const;
    f32 getTime() const;
    glm::ivec2 getSize() const;
    bool isFocussed() const;
    GLFWwindow* getGLFW() const;

private:
    void toggleFullscreen();

    GLFWwindow* m_window;
	bool m_fullscreen;
	bool m_focussed;
	Input m_input;
};
