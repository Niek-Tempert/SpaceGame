#pragma once

#include <providers/time_provider.hpp>
#include <providers/input_provider.hpp>

#include "input.hpp"

class GLFWwindow;

class GLWindow
    : public TimeProvider
    , public InputProvider {
public:
    GLWindow();
    ~GLWindow();
    bool update();
    const Input* getInput() const;
    glm::ivec2 getSize() const;
    bool isFocussed() const;
    f32 getTime();
    f32 getDeltaTime();

private:
    void toggleFullscreen();

    GLFWwindow* m_window;
	bool m_fullscreen;
	bool m_focussed;
	Input m_input;

    f32 m_time;
    f32 m_deltaTime;
};
