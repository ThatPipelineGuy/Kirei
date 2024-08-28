#include "Input.hpp"
#include <iostream>

namespace kirei {

// Singleton instance
Input& Input::instance() {
    static Input input;
    return input;
}

// Register the key callback using a static function that GLFW can call
void Input::registerKeyCallback(GLFWwindow* window, KeyCallback callback) {
    m_keyCallback = std::move(callback);  // Store the callback
    glfwSetKeyCallback(window, keyCallbackInternal);  // Register static callback function
}

// Static function matching GLFW's required callback signature
void Input::keyCallbackInternal(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Forward the call to the instance's keyCallback method
    Input::instance().m_keyCallback(key, scancode, action, mods);
}

}