#include "input_provider.hpp"

#include <engine/input.hpp>

InputProvider::InputProvider(const Input* input) {
    m_input = input;
}

InputProvider::InputProvider(const InputProvider* provider) {
	m_input = provider->m_input;
}

glm::vec2 InputProvider::getCursor() const {
	return m_input->getCursor();
}

glm::vec2 InputProvider::getCursorDelta() const {
	return m_input->getCursorDelta();
}

bool InputProvider::getKey(i32 key) const {
	return m_input->getKey(key);
}

bool InputProvider::getKeyUp(i32 key) const {
	return m_input->getKeyUp(key);
}

bool InputProvider::getKeyDown(i32 key) const {
	return m_input->getKeyDown(key);
}

bool InputProvider::getMouse(i32 button) const {
	return m_input->getMouse(button);
}

bool InputProvider::getMouseUp(i32 button) const {
	return m_input->getMouseUp(button);
}

bool InputProvider::getMouseDown(i32 button) const {
	return m_input->getMouseDown(button);
}
