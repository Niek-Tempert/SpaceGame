#pragma once

#include <glm/vec2.hpp>

class GLWindow;

class CanvasProvider {
public:
    CanvasProvider(const GLWindow* window);
	CanvasProvider(const CanvasProvider* provider);

protected:
    glm::ivec2 getResolution() const;

private:
    const GLWindow* m_window;
};
