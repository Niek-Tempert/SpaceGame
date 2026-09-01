#include "input.hpp"

#define MOUSE_COUNT (GLFW_MOUSE_BUTTON_LAST + 1)

#define KEY_UP_BIT 2
#define KEY_HOLD_BIT 1
#define KEY_DOWN_BIT 0

void Input::keyboardCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
    Input *input = (Input*)glfwGetWindowUserPointer(window);
    
    switch (action) {
        case GLFW_PRESS:
            input->m_keys[key] |= 1 << KEY_DOWN_BIT | ((input->m_keys[key] & 1) ^ 1) << 1;
        break;

        case GLFW_RELEASE:
            input->m_keys[key] &= ~KEY_HOLD_BIT;
            input->m_keys[key] |= 1 << KEY_UP_BIT;
        break;
    }
}

void Input::mouseCallback(GLFWwindow* window, i32 button, i32 action, i32 mods) {
    Input *input = (Input*)glfwGetWindowUserPointer(window);

    u8 flag;
    switch (action) {
        case GLFW_PRESS:
            flag = 1 << button;

            input->m_mouseDownFlags |= flag;
            input->m_mousePressFlags |= flag;
        break;

        case GLFW_RELEASE:
            flag = 1 << button;

            input->m_mouseDownFlags &= ~flag;
            input->m_mouseReleaseFlags |= flag;
        break;
    }
}

void Input::cursorCallback(GLFWwindow* window, f64 xpos, f64 ypos) {
    Input *input = (Input*)glfwGetWindowUserPointer(window);
    
    input->m_cursor = { xpos, ypos };
}

void Input::init(GLFWwindow* window) {
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, cursorCallback);
    glfwSetMouseButtonCallback(window, mouseCallback);
    glfwSetKeyCallback(window, keyboardCallback);

    f64 xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    m_cursor = m_lastCursor = { xpos, ypos };
}

void Input::next() {
    /* Reset mouse flags */
    m_mousePressFlags = 0;
    m_mouseReleaseFlags = 0;

    /* Reset keys */
    for (u8 &key : m_keys) {
        key &= KEY_HOLD_BIT;
    }
    
    m_lastCursor = m_cursor;
}

glm::vec2 Input::getCursor() const {
    return m_cursor;
}

glm::vec2 Input::getCursorDelta() const {
    return m_cursor - m_lastCursor;
}

bool Input::getKey(i32 key) const {
    u8 flag = 1 << KEY_HOLD_BIT;
    return (m_keys[key] & flag) == flag;
}

bool Input::getKeyUp(i32 key) const {
    u8 flag = 1 << KEY_UP_BIT;
    return (m_keys[key] & flag) == flag;
}

bool Input::getKeyDown(i32 key) const {
    u8 flag = 1 << KEY_DOWN_BIT;
    return (m_keys[key] & flag) == flag;
}

bool Input::getMouse(i32 button) const {
    u8 flag = 1 << button;
    return (m_mousePressFlags & flag) == flag;
}

bool Input::getMouseUp(i32 button) const {
    u8 flag = 1 << button;
    return (m_mouseReleaseFlags & flag) == flag;
}

bool Input::getMouseDown(i32 button) const {
    u8 flag = 1 << button;
    return (m_mouseDownFlags & flag) == flag;
}
