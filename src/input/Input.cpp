#include "Input.hpp"
#include <iostream>

namespace kirei {

Input& Input::instance() {
    static Input input;
    return input;
}

void Input::registerKeyCallback(GLFWwindow* window, KeyCallback callback) {
    glfwSetKeyCallback(window, [this, callback = std::move(callback)](GLFWwindow*, int key, int scancode, int action, int mods) {
        keyCallback(key, scancode, action, mods);
    });
    m_keyCallback = std::move(callback);
}

void Input::keyCallback(int key, int scancode, int action, int mods) {
    if (m_keyCallback) m_keyCallback(key, scancode, action, mods);
}

} // namespace kirei
