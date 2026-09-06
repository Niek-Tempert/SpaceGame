#include "input_provider.hpp"

#include <engine/glwindow.hpp>

InputProvider::InputProvider(const GLWindow* window) {
    m_window = window;
}

InputProvider::InputProvider(const InputProvider* provider) {
	m_window = provider->m_window;
}

glm::vec2 InputProvider::getCursor() const {
	return m_window->getInput()->getCursor();
}

glm::vec2 InputProvider::getCursorDelta() const {
	return m_window->getInput()->getCursorDelta();
}

bool InputProvider::getKey(i32 key) const {
	return m_window->getInput()->getKey(key);
}

bool InputProvider::getKeyUp(i32 key) const {
	return m_window->getInput()->getKeyUp(key);
}

bool InputProvider::getKeyDown(i32 key) const {
	return m_window->getInput()->getKeyDown(key);
}

bool InputProvider::getMouse(i32 button) const {
	return m_window->getInput()->getMouse(button);
}

bool InputProvider::getMouseUp(i32 button) const {
	return m_window->getInput()->getMouseUp(button);
}

bool InputProvider::getMouseDown(i32 button) const {
	return m_window->getInput()->getMouseDown(button);
}
