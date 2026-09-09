#include "canvas_provider.hpp"

#include <engine/glwindow.hpp>

CanvasProvider::CanvasProvider(const GLWindow *window) {
	m_window = window;
}

CanvasProvider::CanvasProvider(const CanvasProvider *provider) {
	m_window = provider->m_window;
}

glm::ivec2 CanvasProvider::getSize() const {
	return m_window->getSize();
}
