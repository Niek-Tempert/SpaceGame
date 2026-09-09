#pragma once

#include <glm/glm.hpp>

class GLWindow;

class CanvasProvider {
public:
    CanvasProvider(const GLWindow* window);
	CanvasProvider(const CanvasProvider* provider);

    glm::ivec2 getSize() const;

private:
    const GLWindow* m_window;
};
